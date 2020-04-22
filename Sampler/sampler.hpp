#ifndef SAMPLER_HPP
#define SAMPLER_HPP

#include <random>

class Sampler
{
public:
    Sampler(int numSamples, int numSets) :
        mNumSamples{ numSamples }, mNumSets{ numSets }, mCount{ 0 }, mJump{ 0 }
    {
        mSamples.reserve(mNumSets* mNumSamples);
        setupShuffledIndeces();
        distribution = std::uniform_int_distribution<int>(0,std::numeric_limits<int>::max());
    }

    virtual ~Sampler() = default;

    int getNumSamples() const
    {
        return mNumSamples;
    }

    void setupShuffledIndeces() {
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

    virtual void generateSamples() = 0;

    maths::Point3D sampleUnitSquare() {
        if (mCount % mNumSamples == 0)
	    {
	      mJump = (distribution(generator_) % mNumSets) * mNumSamples;
        }
        return mSamples[mJump + mShuffledIndeces[mJump + mCount++ % mNumSamples]];
    }

protected:
  std::uniform_int_distribution<int> distribution;
  std::default_random_engine generator_;
  std::vector<maths::Point3D> mSamples;
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

    void generateSamples()
    {
      int n = static_cast<int>(std::sqrt(static_cast<float>(mNumSamples)));

        for (int j = 0; j < mNumSets; ++j)
        {
            for (int p = 0; p < n; ++p)
            {
                for (int q = 0; q < n; ++q)
                {
                    mSamples.push_back(
                        maths::Point3D{ (q + 0.5f) / n, (p + 0.5f) / n, 0.0f });
                }
            }
        }
    }
};

#endif
