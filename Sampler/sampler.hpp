#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include <random>

#include "Maths/maths.hpp"

class Sampler {
public:
  Sampler(int numSamples, int numSets) :
    mNumSamples{ numSamples }, mNumSets{ numSets }, mCount{ 0 }, mJump{ 0 }
  {
    samples_.reserve(mNumSets* mNumSamples);
    setupShuffledIndeces();
    distribution_ = std::uniform_int_distribution<int>(0,std::numeric_limits<int>::max());
  }

  virtual ~Sampler() = default;

  int getNumSamples() const
  {
    return mNumSamples;
  }

  void setupShuffledIndeces();

  virtual void generateSamples() = 0;

  maths::Point3D sampleUnitSquare();

protected:
  std::uniform_int_distribution<int> distribution_;
  std::default_random_engine generator_;
  std::vector<maths::Point3D> samples_;
  std::vector<int> mShuffledIndeces;

  int mNumSamples;
  int mNumSets;
  unsigned long mCount;
  int mJump;
};

class Regular : public Sampler
{
public:
  Regular(int numSamples, int numSets) : Sampler{ numSamples, numSets }
  {
    generateSamples();
  }

  void generateSamples();
  
};

#endif
