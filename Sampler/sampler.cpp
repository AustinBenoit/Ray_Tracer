#include "Sampler/sampler.hpp"

#include "Maths/maths.hpp"

void Sampler::setupShuffledIndeces()
{
  mShuffledIndeces.reserve(mNumSamples * mNumSets);
  std::vector<int> indices;

  std::random_device d;
  std::mt19937 generator(d());

  for (int j = 0; j < mNumSamples; ++j)
    {
      indices.push_back(j);
    }

  for (int p = 0; p < mNumSets; ++p)
    {
      std::shuffle(indices.begin(), indices.end(), generator);

      for (int j = 0; j < mNumSamples; ++j)
	{
	  mShuffledIndeces.push_back(indices[j]);
	}
    }
}


maths::Point3D Sampler::sampleUnitSquare() {
  if (mCount % mNumSamples == 0)
    {
      mJump = (distribution_(generator_) % mNumSets) * mNumSamples;
    }
  return samples_[mJump + mShuffledIndeces[mJump + mCount++ % mNumSamples]];
}


void Regular::generateSamples()
{
  int n = static_cast<int>(std::sqrt(static_cast<float>(mNumSamples)));

  for (int j = 0; j < mNumSets; ++j)
    {
      for (int p = 0; p < n; ++p)
	{
	  for (int q = 0; q < n; ++q)
	    {
	      samples_.push_back(
				 maths::Point3D{ (q + 0.5f) / n, (p + 0.5f) / n, 0.0f });
	    }
	}
    }
}
