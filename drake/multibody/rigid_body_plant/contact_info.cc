#include "drake/multibody/rigid_body_plant/contact_info.h"

using std::move;

namespace drake {
namespace systems {

template <typename T>
ContactInfo<T>::ContactInfo(DrakeCollision::ElementId element1,
                            DrakeCollision::ElementId element2)
    : element1_(element1),
      element2_(element2),
      resultant_force_(),
      contact_details_() {}

// TODO(jwnimmer-tri) This constructor (and the corresponding assignment
// operator below) could be automatically generated by the compiler, if the
// "details_" vector were copyable.  We should make them so by replacing
// unique_ptr with a clone_ptr that uses Clone() to perform a copy, e.g.,
// https://github.com/simbody/simbody/blob/master/SimTKcommon/include/SimTKcommon/internal/ClonePtr.h
template <typename T>
ContactInfo<T>::ContactInfo(const ContactInfo<T>& other)
    : element1_(other.element1_),
      element2_(other.element2_),
      resultant_force_(other.resultant_force_) {
  contact_details_.reserve(other.contact_details_.size());
  for (const auto& detail : other.contact_details_) {
    contact_details_.emplace_back(detail->Clone());
  }
}

template <typename T>
ContactInfo<T>& ContactInfo<T>::operator=(const ContactInfo<T>& other) {
  if (this == &other) return *this;
  element1_ = other.element1_;
  element2_ = other.element2_;
  resultant_force_ = other.resultant_force_;
  contact_details_.clear();
  contact_details_.reserve(other.contact_details_.size());
  for (const auto& detail : other.contact_details_) {
    contact_details_.emplace_back(detail->Clone());
  }
  return *this;
}

// Explicitly instantiates on the most common scalar types.
template class ContactInfo<double>;

}  // namespace systems
}  // namespace drake
