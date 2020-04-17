#ifndef SAMPLER_HPP
#define SAMPLER_HPP

class Sampler
{
public:
    Sampler(int numSamples, int numSets) :
        mNumSamples{ numSamples }, mNumSets{ numSets }, mCount{ 0 }, mJump{ 0 }
    {
        mSamples.reserve(mNumSets* mNumSamples);
        setupShuffledIndeces();
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
	  //atlas::math::Random<int> engine;
	  // mJump = (engine.getRandomMax() % mNumSets) * mNumSamples;
        }

        return  {0.5f, 0.5f, 0.0f};// mSamples[mJump + mShuffledIndeces[mJump + mCount++ % mNumSamples]];
    }

protected:
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
