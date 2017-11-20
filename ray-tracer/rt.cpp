#include "structures.h"

#include <fstream>
#include <vector>

#define MAX_RAY_DEPTH 5
#define BIAS 1e-4

float mix(const float &a, const float &b, const float &mix) {
  return b * mix + a * (1 - mix);
}

vector3<float> trace(const vector3<float> &rayorig,
                     const vector3<float> &raydir,
                     const std::vector<sphere> &spheres, const int &depth) {
  float tnear = INFINITY;
  const sphere *sp = nullptr;
  for (const auto &s : spheres) {
    float t[] = {INFINITY};
    if (s.intersect(rayorig, raydir, static_cast<float *>(t)) && t[0] < tnear) {
      tnear = t[0], sp = &s;
    }
  }

  if (sp == nullptr) {
    return vector3<float>{2};
  }

  vector3<float> sf_color{0}, point_it = rayorig + raydir * tnear,
                              norm_it{point_it - sp->center, true};
  bool inside = false;
  if (raydir.dot(norm_it) > 0) {
    norm_it = -norm_it, inside = true;
  }

  if ((sp->transparency > 0 || sp->reflection > 0) && depth < MAX_RAY_DEPTH) {
    float facing_ratio = -raydir.dot(norm_it),
          fresnel = mix(pow(1 - facing_ratio, 3), 1, 0.1);

    vector3<float> refldir{raydir - norm_it * 2 * raydir.dot(norm_it), true},
        refl = trace(point_it + norm_it * BIAS, refldir, spheres, depth + 1),
        refrac{0};

    if (sp->transparency != 0.0f) {
      float ior = 1.1, eta = (inside) ? ior : 1 / ior,
            cosi = -norm_it.dot(raydir), k = 1 - eta * eta * (1 - cosi * cosi);
      vector3<float> refr_dir{raydir * eta + norm_it * (eta * cosi - sqrt(k)),
                              true};
      refrac = trace(point_it - norm_it * BIAS, refr_dir, spheres, depth + 1);
    }

    sf_color = (refl * fresnel + refrac * (1 - fresnel) * sp->transparency) *
               sp->sf_color;
  } else {
    for (const auto &s : spheres) {
      if (s.em_color.x > 0) {
        vector3<float> transmission{1}, light_dir{s.center - point_it, true};
        for (const auto &ss : spheres) {
          float t[] = {INFINITY};
          if (&s != &ss && ss.intersect(point_it + norm_it * BIAS, light_dir,
                                        static_cast<float *>(t))) {
            transmission = vector3<float>{0};
            break;
          }
        }
        sf_color += sp->sf_color * transmission *
                    std::max(float(0), norm_it.dot(light_dir)) * s.em_color;
      }
    }
  }

  return sf_color + sp->em_color;
}

std::vector<vector3<float>> render(uint32_t width, uint32_t height,
                                   const std::vector<sphere> &spheres) {
  std::vector<vector3<float>> pixels(width * height);
  float inv_width = 1 / float(width), inv_height = 1 / float(height), fov = 30,
        aspect_ratio = width / float(height), angle = tan(M_PI * fov / 360.);

  for (uint32_t y = 0; y < height; ++y) {
    for (uint32_t x = 0; x < width; ++x) {
      float xx = (2 * ((x + 0.5) * inv_width) - 1) * angle * aspect_ratio;
      float yy = (1 - 2 * ((y + 0.5) * inv_height)) * angle;
      vector3<float> raydir(xx, yy, -1, true);
      pixels[y * width + x] = trace(vector3<float>(0), raydir, spheres, 0);
    }
  }

  return pixels;
}

void write_ppm(uint32_t width, uint32_t height,
               const std::vector<vector3<float>> &image) {
  std::cout << "P6" << std::endl
            << width << " " << height << std::endl
            << "255" << std::endl;
  for (const auto &pixel : image) {
    std::cout << static_cast<uint8_t>(std::min(float(1), pixel.x) * 255)
              << static_cast<uint8_t>(std::min(float(1), pixel.y) * 255)
              << static_cast<uint8_t>(std::min(float(1), pixel.z) * 255);
  }
}

int32_t main(int32_t argc, char **argv) {
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " input_file" << std::endl;
    exit(EXIT_FAILURE);
  }

  std::ifstream file(argv[1]);
  uint32_t width, height, n_spheres, n_lights, i;
  std::vector<sphere> spheres;
  float x_pos, y_pos, z_pos, radius, x_clr, y_clr, z_clr, refl, transp, ec = 0;

  file >> width >> height;
  file >> n_spheres >> n_lights;
  for (i = 0; i < n_spheres + n_lights; ++i) {
    file >> x_pos >> y_pos >> z_pos >> radius >> x_clr >> y_clr >> z_clr >>
        refl >> transp;
    if (i >= n_spheres) {
      file >> ec;
    }
    vector3<float> position(x_pos, y_pos, z_pos);
    vector3<float> color(x_clr, y_clr, z_clr);
    vector3<float> em_clr(ec);
    spheres.emplace_back(position, radius, color, refl, transp, em_clr);
  }
  file.close();

  write_ppm(width, height, render(width, height, spheres));

  return EXIT_SUCCESS;
}
