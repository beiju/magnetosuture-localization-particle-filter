#include <filesystem>
#include <iostream>

#include "lib/pf/bootstrap_filter.h"
#include "lib/pf/resamplers.h"
#include "csv.hpp"

#define WHICH_CURRENT "measured_current_filtered"

constexpr size_t kNumParticles = 500;
constexpr size_t kStateDimensions = 6; // position and velocity for each of x, y, angle
constexpr size_t kObservationDimensions = 3; // position only for each of x, y, angle
constexpr bool kDebugFilter = true;

namespace fs = std::filesystem;

struct Sample {
  size_t frame_no;

  double current_north;
  double current_south;
  double current_east;
  double current_west;

  double localization_x;
  double localization_y;
  double localization_angle;
};

using FloatT = float;
using MyResampler = pf::resamplers::systematic_resampler<kNumParticles, kStateDimensions, FloatT>;
class MyPf : public pf::filters::BSFilter<kNumParticles,
                                          kStateDimensions,
                                          kObservationDimensions,
                                          MyResampler,
                                          FloatT,
                                          kDebugFilter> {

  float_t logMuEv(const state_sized_vec& x1) override {
    std::abort();
    return {};
  }

  state_sized_vec q1Samp(const obs_sized_vec& y1) override {
    std::abort();
    return {};
  }

  float_t logQ1Ev(const state_sized_vec& x1, const obs_sized_vec & y1) override {
    std::abort();
    return {};
  }

  float_t logGEv(const obs_sized_vec& yt, const state_sized_vec& xt) override {
    std::abort();
    return {};
  }

  state_sized_vec fSamp(const state_sized_vec& xtm1) override {
    std::abort();
    return {};
  }
};


int main(int argc, char** argv) {
  for (int i = 0; i < argc; i++) {
    std::cout << i << ": " << argv[i] << "\n";
  }
  std::cout << std::flush;

  if (argc != 2) {
    std::cerr << "Usage: particle_filter_test path_to_recording" << std::endl;
    return 1;
  }

  fs::path experiment_path(argv[1]);
  csv::CSVReader reader((experiment_path / "data.csv").string());

  for (csv::CSVRow& row: reader) { // Input iterator
    auto sample = Sample {
      .frame_no = row["camera_frame_number"].get<size_t>(),

      .current_north = row[WHICH_CURRENT "_north"].get<double>(),
      .current_south = row[WHICH_CURRENT "_south"].get<double>(),
      .current_east = row[WHICH_CURRENT "_east"].get<double>(),
      .current_west = row[WHICH_CURRENT "_west"].get<double>(),

      .localization_x = row["localization_x"].get<double>(),
      .localization_y = row["localization_y"].get<double>(),
      .localization_angle = row["localization_angle"].get<double>(),
    };

    std::cout << "Got frame " << sample.frame_no << std::endl;
  }

  MyPf pf;
  return 0;
}
