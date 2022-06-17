#include <iostream>

#include "lib/pf/bootstrap_filter.h"
#include "lib/pf/resamplers.h"

constexpr size_t kNumParticles = 500;
constexpr size_t kStateDimensions = 6; // position and velocity for each of x, y, angle
constexpr size_t kObservationDimensions = 3; // position only for each of x, y, angle
constexpr bool kDebugFilter = true;

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


int main() {
  MyPf pf;
  return 0;
}
