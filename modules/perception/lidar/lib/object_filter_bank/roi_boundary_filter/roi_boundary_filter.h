/******************************************************************************
 * Copyright 2018 The Apollo Authors. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
#ifndef MODULES_PERCEPTION_LIDAR_LIB_OBJECT_FILTER_BANK_ROI_BOUNDARY_FILTER_H_
#define MODULES_PERCEPTION_LIDAR_LIB_OBJECT_FILTER_BANK_ROI_BOUNDARY_FILTER_H_

#include <Eigen/Dense>
#include <string>
#include <vector>

#include "modules/perception/base/point_cloud_types.h"
#include "modules/perception/lidar/lib/interface/base_object_filter.h"

namespace apollo {
namespace perception {
namespace lidar {

class ROIBoundaryFilter : public BaseObjectFilter {
 public:
  ROIBoundaryFilter() = default;

  virtual ~ROIBoundaryFilter() = default;

  bool Init(const ObjectFilterInitOptions& options =
                ObjectFilterInitOptions()) override;

  // @brief: filter objects
  // @param [in]: options
  // @param [in/out]: frame
  // segmented_objects should be valid, and will be filtered,
  bool Filter(const ObjectFilterOptions& options, LidarFrame* frame) override;

  std::string Name() const override { return "ROIBoundaryFilter"; }

 private:
  // @brief: given input objects, build polygon in world frame
  void BuildWorldPolygons(const ObjectFilterOptions& options,
                          const LidarFrame& frame);
  // @brief: fill is_in_roi in lidar object supplement
  void FillObjectRoiFlag(const ObjectFilterOptions& options, LidarFrame* frame);
  // @brief: filter outside objects based on distance to boundary
  void FilterObjectsOutsideBoundary(const ObjectFilterOptions& options,
                                    LidarFrame* frame,
                                    std::vector<bool>* objects_valid_flag);
  // @brief: filter inside objects based on distance to boundary
  void FilterObjectsInsideBoundary(const ObjectFilterOptions& options,
                                   LidarFrame* frame,
                                   std::vector<bool>* objects_valid_flag);
  // @brief: filter objects based on position and confidence
  void FilterObjectsByConfidence(const ObjectFilterOptions& options,
                                 LidarFrame* frame,
                                 std::vector<bool>* objects_valid_flag);

 private:
  std::vector<base::PolygonDType> polygons_in_world_;
  std::vector<bool> objects_cross_roi_;
  std::vector<bool> objects_valid_flag_;
  // params
  double distance_to_boundary_threshold_ = 1.0;
  double inside_threshold_ = 1.0;
  float confidence_threshold_ = 0.5f;
  float cross_roi_threshold_ = 0.6f;
};  // class ROIBoundaryFilter

}  // namespace lidar
}  // namespace perception
}  // namespace apollo

#endif  // MODULES_PERCEPTION_LIDAR_LIB_OBJECT_FILTER_BANK_ROI_BOUNDARY_FILTER_H_
