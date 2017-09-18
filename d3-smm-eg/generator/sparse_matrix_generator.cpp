#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <fstream>
#include <random>

//RANGE(a): used to define value limits for matrix cells
#define RANGE(a) ((a % 10)+1)

template <class T> class Row {
    typedef std::pair<size_t, T> Cell;  //Cell inside a row: contains a column and a value
    private:
        std::list< Cell > data;         //Cells in the row
        size_t pos;                     //Position of the row

    public:
        Row () { }
        Row (size_t r) {
            pos = r;
        }

        /* Checks if the row has a cell in column c */
        bool hasItem (size_t c) {
            bool found = false;
            typename std::list< Cell >::iterator it;
            // Stops the search if it passes by where the column should be
            for (it = data.begin(); it!=data.end() && it->first <= c; ++it) // short circuit keeps us safe from errors here
                if (it->first == c){
                    found = true;
                    break;
                }
            return found;
        }

		/* Returns data from a row */
        std::list< Cell > getRowData() {
            return data;
        }

        /* Returns the value of the cell in column c */
        T& operator()(size_t c) {
            typename std::list< Cell >::iterator it = data.begin();
            // Goes through the row until it finds the cell
            while (it->first != c) ++it;
            return it->second;
        }

        /* Inserts a new cell in the row keeping it sorted by columns */
        void insert (size_t c, T value) {
            typename std::list< Cell >::iterator it = data.begin();
            // Finds the correct position for the cell
            while ((it!= data.end()) && (it->first < c)) ++it;
            data.insert(it,std::make_pair(c,value));
        }

        /* Writes the contents of a row to a file */
        void writeOutput (std::ofstream& file) {
            //Write each line as: row column value
            for (auto cell: data)
                file << pos << " " << cell.first << " " << cell.second << "\n";
        }

        /* Inner product of two arrays */
        static T innerProduct (std::list< Cell > row1, std::list< Cell > row2) {
            T result = 0;
            typename std::list< Cell >::iterator cell1 = row1.begin();
            typename std::list< Cell >::iterator cell2 = row2.begin();

            //While we have items in one or the other array
            while ((cell1 != row1.end()) && (cell2 != row2.end())){
                //if they have the same index, multiply
                if (cell1->first == cell2->first) {
                    result += cell1->second * cell2->second;
                    ++cell1;
                    ++cell2;
                } else { //if they don't, we try to find the next possible pair
                    if (cell1->first < cell2->first) ++cell1;
                    else ++cell2;
                }

            }
            return result;
        }

};

template <class T> class SparseMatrix {
    typedef std::pair<size_t, T> Cell;  //Cell inside a row: contains a column and a value
    private:
        std::vector< Row<T> > data; // Array of rows
        size_t dim1;                // Number of rows
        size_t dim2;                // Number of columns
        size_t size;                // Number of cells in the matrix

    public:
        SparseMatrix () { }
        SparseMatrix (size_t r, size_t c) {
            dim1 = r;
            dim2 = c;
            data = std::vector< Row<T> >(dim1);
            for (size_t i = 0; i < dim1; ++i)
                data[i] = Row<T>(i);
            size = 0;
        }

		/* Returns data from row r */
        std::list< Cell > getRowData(size_t r) {
            return data[r].getRowData();
        }

        /* Returns the value of the cell in row r, column c */
        T& operator()(size_t r, size_t c) {
            return data[r](c);
        }

        /* Checks if the row r has a cell in column c */
        bool hasItem (size_t r, size_t c) {
            return data[r].hasItem(c);
        }

        /* Inserts a new cell in row r */
        void insert (size_t r, size_t c, T value) {
            if (value != 0){
                data[r].insert(c, value);
                ++size; //A new cell has been added to the matrix
            }
        }

        /* Writes the contents of the matrix to a file */
        void writeOutput (std::ofstream& file) {
            //First line of the file: rows, columns and items
            file << dim1 << " " << dim2 << " " << size << "\n";
            //Then writes the cells in its rows in order
            for (auto row: data) row.writeOutput(file);
        }

        size_t rows() {return dim1;}
        size_t columns() {return dim2;}

};

int main(int argc, char *argv[]) {

    if (argc < 6) {
        std::cerr << "Usage: " << argv[0] << " [rows] [columns] [non-zeros] [seed] [output file]" << std::endl;
        return 1;
    }

    //inputs
    size_t rows, columns, nonzeros, seed;
    rows = std::stoi(argv[1]);
    columns = std::stoi(argv[2]);
    nonzeros = std::stoi(argv[3]);
    seed = std::stoi(argv[4]);

    //Matrix to generate
    SparseMatrix<int> matrix(rows,columns);

    //Generates nonzeros
    size_t r, c;
    size_t i = nonzeros;
    std::mt19937 rand (seed);
    while (i > 0) {             //for the number of non zeros
        r = rand() % rows;      //randomize a row
        c = rand() % columns;   //randomize a column
        // if we do not have a cell like this in the matrix, we add one
        if(! matrix.hasItem(r,c)){
            matrix.insert(r,c,RANGE(rand()));
            --i;
        }
    }

    //Write output
    std::ofstream outfile;
    outfile.exceptions (std::ofstream::failbit | std::ofstream::badbit);
    try {
        outfile.open(argv[5]);
        matrix.writeOutput(outfile);
        outfile.close();
    } catch (std::ofstream::failure e) {
        std::cerr << "Exception handling output file" << argv[1];
    }

}
