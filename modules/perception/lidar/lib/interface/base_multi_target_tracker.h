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
#ifndef MODULES_PERCEPTION_LIDAR_LIB_INTERFACE_BASE_MULTI_TARGET_TRACKER_H_
#define MODULES_PERCEPTION_LIDAR_LIB_INTERFACE_BASE_MULTI_TARGET_TRACKER_H_

#include <string>
#include <vector>

#include "modules/perception/lib/registerer/registerer.h"
#include "modules/perception/lidar/common/lidar_frame.h"

namespace apollo {
namespace perception {
namespace lidar {

struct MultiTargetTrackerInitOptions {};

struct MultiTargetTrackerOptions {};

class BaseMultiTargetTracker {
 public:
  BaseMultiTargetTracker() = default;

  ~BaseMultiTargetTracker() = default;

  virtual bool Init(const MultiTargetTrackerInitOptions& options =
                        MultiTargetTrackerInitOptions()) = 0;

  // @brief: track segmented objects, and estimate motion
  // @param [in]: options
  // @param [in/out]: tracked object
  // tracked objects should be filled, required,
  virtual bool Track(const MultiTargetTrackerOptions& options,
                     LidarFrame* frame) = 0;

  virtual std::string Name() const = 0;

  BaseMultiTargetTracker(const BaseMultiTargetTracker& rhs) = delete;

  BaseMultiTargetTracker& operator=(const BaseMultiTargetTracker&) = delete;

 private:
};  // class BaseMultiTargetTracker

PERCEPTION_REGISTER_REGISTERER(BaseMultiTargetTracker);
#define PERCEPTION_REGISTER_MULTITARGET_TRACKER(name) \
  PERCEPTION_REGISTER_CLASS(BaseMultiTargetTracker, name)

}  // namespace lidar
}  // namespace perception
}  // namespace apollo

#endif  // MODULES_PERCEPTION_LIDAR_LIB_INTERFACE_BASE_MULTI_TARGET_TRACKER_H_
