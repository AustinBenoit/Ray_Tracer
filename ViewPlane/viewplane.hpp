#ifndef VIEWPLANE_HPP
#define VIEWPLANE_HPP

// to be removed once I have completed the sampler class


class ViewPlane {
public:
  std::size_t x_resolution_;
  std::size_t y_resolution_;
  
 // Sampler* sampler_ptr_;
 // int num_samples_;
  int max_depth;
  
  ViewPlane() {}
  ViewPlane(std::size_t x_resolution, std::size_t y_resolution) :
    x_resolution_{ x_resolution },
    y_resolution_{ y_resolution }
  {}
  
  ViewPlane(const ViewPlane& p) {
    x_resolution_ = p.x_resolution_;
    y_resolution_ = p.y_resolution_;
//    sampler_ptr_ = p.sampler_ptr_;
//    num_samples_ = p.num_samples_;
  }
  
  void SetMaxDepth(int depth) {
    max_depth = depth;
  }
  
  void SetResolution(std::size_t x, std::size_t y) {
    x_resolution_ = x;
    y_resolution_ = y;
  }
  
//  void set_sampler(Sampler* sp) {
//    num_samples_ = sp->getNumSamples();
//    sampler_ptr_ = sp;
//  }
  
};

#endif
