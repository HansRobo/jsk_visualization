// -*- mode: c++; -*-
/*********************************************************************
 * Software License Agreement (BSD License)
 *
 *  Copyright (c) 2014, JSK Lab
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions
 *  are met:
 *
 *   * Redistributions of source code must retain the above copyright
 *     notice, this list of conditions and the following disclaimer.
 *   * Redistributions in binary form must reproduce the above
 *     copyright notice, this list of conditions and the following
 *     disclaimer in the documentation and/o2r other materials provided
 *     with the distribution.
 *   * Neither the name of the JSK Lab nor the names of its
 *     contributors may be used to endorse or promote products derived
 *     from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *  FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 *  COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 *  INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 *  BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 *  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 *  LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 *  ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGE.
 *********************************************************************/

#ifndef JSK_RVIZ_PLUGINS_PIE_CHART_DISPLAY_H_
#define JSK_RVIZ_PLUGINS_PIE_CHART_DISPLAY_H_
#include <std_msgs/msg/float32.hpp>
#ifndef Q_MOC_RUN
#include "rviz_common/ros_topic_display.hpp"
// #include "rviz_default_plugins/visibility_control.hpp"
#include "overlay_utils.hpp"
#include <OgreColourValue.h>
#include <OgreTexture.h>
#include <OgreMaterial.h>
#include <rviz_common/properties/int_property.hpp>
#include <rviz_common/properties/float_property.hpp>
#include <rviz_common/properties/color_property.hpp>
#include <rviz_common/properties/bool_property.hpp>
#include <rviz_common/properties/ros_topic_property.hpp>
#endif

namespace jsk_rviz_plugins
{
  class PieChartDisplay
    : public rviz_common::RosTopicDisplay<std_msgs::msg::Float32>
  {
    Q_OBJECT
  public:
    PieChartDisplay();
    ~PieChartDisplay();
    
    // methods for OverlayPickerTool
    bool isInRegion(int x, int y);
    void movePosition(int x, int y);
    void setPosition(int x, int y);
    int getX() { return left_; };
    int getY() { return top_; };

  protected:
    void onEnable() override;
    void onDisable() override;
    void onInitialize() override;
    void processMessage(std_msgs::msg::Float32::ConstSharedPtr msg) override;
    void drawPlot(double val);
    void update(float wall_dt, float ros_dt) override;
    void reset() override;
    // properties
    rviz_common::properties::IntProperty* size_property_;
    rviz_common::properties::IntProperty* left_property_;
    rviz_common::properties::IntProperty* top_property_;
    rviz_common::properties::ColorProperty* fg_color_property_;
    rviz_common::properties::ColorProperty* bg_color_property_;
    rviz_common::properties::ColorProperty* text_color_property_;
    rviz_common::properties::FloatProperty* fg_alpha_property_;
    rviz_common::properties::FloatProperty* fg_alpha2_property_;
    rviz_common::properties::FloatProperty* bg_alpha_property_;
    rviz_common::properties::FloatProperty* text_alpha_property_;
    rviz_common::properties::IntProperty* text_size_property_;
    rviz_common::properties::FloatProperty* max_value_property_;
    rviz_common::properties::FloatProperty* min_value_property_;
    rviz_common::properties::BoolProperty* show_caption_property_;
    rviz_common::properties::BoolProperty* auto_color_change_property_;
    rviz_common::properties::ColorProperty* max_color_property_;
    rviz_common::properties::BoolProperty* clockwise_rotate_property_;

    int left_;
    int top_;
    uint16_t texture_size_;
    QColor fg_color_;
    QColor bg_color_;
    QColor max_color_;
    int text_size_;
    bool show_caption_;
    bool auto_color_change_;
    int caption_offset_;
    double fg_alpha_;
    double fg_alpha2_;
    double bg_alpha_;
    double max_value_;
    double min_value_;
    float data_;
    bool update_required_;
    bool first_time_;
    OverlayObject::Ptr overlay_;
    bool clockwise_rotate_;
    
    std::mutex mutex_;
                       
  protected Q_SLOTS:
    void updateTopic();
    void updateSize();
    void updateTop();
    void updateLeft();
    void updateBGColor();
    void updateTextSize();
    void updateFGColor();
    void updateFGAlpha();
    void updateFGAlpha2();
    void updateBGAlpha();
    void updateMinValue();
    void updateMaxValue();
    void updateShowCaption();
    void updateAutoColorChange();
    void updateMaxColor();
    void updateClockwiseRotate();

  private:
  };

}

#endif