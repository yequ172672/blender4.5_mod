/* SPDX-FileCopyrightText: 2023 Blender Authors
 *
 * SPDX-License-Identifier: Apache-2.0 */

#include "BLI_string_utils.hh"

#include <string>

#include "testing/testing.h"

#include "BLI_vector.hh"

namespace blender {

TEST(BLI_string_utils, BLI_string_replace)
{
  {
    std::string s = "foo bar baz";
    BLI_string_replace(s, "bar", "hello");
    EXPECT_EQ(s, "foo hello baz");
  }

  {
    std::string s = "foo bar baz world bar";
    BLI_string_replace(s, "bar", "hello");
    EXPECT_EQ(s, "foo hello baz world hello");
  }
}

TEST(BLI_string_utils, BLI_uniquename_cb)
{
  const Vector<std::string> current_names{"Foo", "Bar", "Bar.003", "Baz.001", "Big.999"};

  {
    auto unique_check_func = [&](const StringRef check_name) {
      return current_names.contains(check_name);
    };

    {
      char name[64] = "";
      BLI_uniquename_cb(unique_check_func, "Default Name", '.', name, sizeof(name));
      EXPECT_STREQ(name, "Default Name");
    }

    {
      char name[64] = "Baz";
      BLI_uniquename_cb(unique_check_func, "Default Name", '.', name, sizeof(name));
      EXPECT_STREQ(name, "Baz");
    }

    {
      char name[64] = "Foo";
      BLI_uniquename_cb(unique_check_func, "Default Name", '.', name, sizeof(name));
      EXPECT_STREQ(name, "Foo.001");
    }

    {
      char name[64] = "Baz.001";
      BLI_uniquename_cb(unique_check_func, "Default Name", '.', name, sizeof(name));
      EXPECT_STREQ(name, "Baz.002");
    }

    {
      char name[64] = "Bar.003";
      BLI_uniquename_cb(unique_check_func, "Default Name", '.', name, sizeof(name));
      EXPECT_STREQ(name, "Bar.004");
    }

    {
      char name[64] = "Big.999";
      BLI_uniquename_cb(unique_check_func, "Default Name", '.', name, sizeof(name));
      EXPECT_STREQ(name, "Big.1000");
    }
  }

  {
    const auto unique_check = [&](const blender::StringRef name) -> bool {
      return current_names.contains(name);
    };

    EXPECT_EQ(BLI_uniquename_cb(unique_check, '.', ""), "");
    EXPECT_EQ(BLI_uniquename_cb(unique_check, '.', "Baz"), "Baz");
    EXPECT_EQ(BLI_uniquename_cb(unique_check, '.', "Foo"), "Foo.001");
    EXPECT_EQ(BLI_uniquename_cb(unique_check, '.', "Baz.001"), "Baz.002");
    EXPECT_EQ(BLI_uniquename_cb(unique_check, '.', "Bar.003"), "Bar.004");
    EXPECT_EQ(BLI_uniquename_cb(unique_check, '.', "Big.999"), "Big.1000");
  }
}

TEST(BLI_string_utils, BLI_string_flip_side_name)
{
  char result[64];

  /* Existing behavior: suffix single letter. */
  BLI_string_flip_side_name(result, "Bone.L", false, sizeof(result));
  EXPECT_STREQ(result, "Bone.R");

  BLI_string_flip_side_name(result, "Bone_R", false, sizeof(result));
  EXPECT_STREQ(result, "Bone_L");

  /* Existing behavior: prefix single letter. */
  BLI_string_flip_side_name(result, "L_Bone", false, sizeof(result));
  EXPECT_STREQ(result, "R_Bone");

  BLI_string_flip_side_name(result, "L-Bone", false, sizeof(result));
  EXPECT_STREQ(result, "R-Bone");

  /* Existing behavior: full word at start/end. */
  BLI_string_flip_side_name(result, "leftArm", false, sizeof(result));
  EXPECT_STREQ(result, "rightArm");

  BLI_string_flip_side_name(result, "Arm_right", false, sizeof(result));
  EXPECT_STREQ(result, "Arm_left");

  BLI_string_flip_side_name(result, "RIGHT_arm", false, sizeof(result));
  EXPECT_STREQ(result, "LEFT_arm");

  /* No marker: unchanged. */
  BLI_string_flip_side_name(result, "Spine", false, sizeof(result));
  EXPECT_STREQ(result, "Spine");

  /* New behavior: mid-string markers with separators. */
  BLI_string_flip_side_name(result, "bip001-L-UpperArm", false, sizeof(result));
  EXPECT_STREQ(result, "bip001-R-UpperArm");

  BLI_string_flip_side_name(result, "bip001 L UpperArm", false, sizeof(result));
  EXPECT_STREQ(result, "bip001 R UpperArm");

  BLI_string_flip_side_name(result, "bip001.L.UpperArm", false, sizeof(result));
  EXPECT_STREQ(result, "bip001.R.UpperArm");

  BLI_string_flip_side_name(result, "bip001_left_upper", false, sizeof(result));
  EXPECT_STREQ(result, "bip001_right_upper");

  BLI_string_flip_side_name(result, "Bone-L-001", false, sizeof(result));
  EXPECT_STREQ(result, "Bone-R-001");

  BLI_string_flip_side_name(result, "bip001-left-hand", false, sizeof(result));
  EXPECT_STREQ(result, "bip001-right-hand");

  /* New behavior: camelCase boundaries. */
  BLI_string_flip_side_name(result, "ManLeftHand", false, sizeof(result));
  EXPECT_STREQ(result, "ManRightHand");

  BLI_string_flip_side_name(result, "bip001RightHand", false, sizeof(result));
  EXPECT_STREQ(result, "bip001LeftHand");

  BLI_string_flip_side_name(result, "ManRight", false, sizeof(result));
  EXPECT_STREQ(result, "ManLeft");

  /* Edge cases. */
  BLI_string_flip_side_name(result, "L", false, sizeof(result));
  EXPECT_STREQ(result, "L");

  BLI_string_flip_side_name(result, "ArmLength", false, sizeof(result));
  EXPECT_STREQ(result, "ArmLength");
}

}  // namespace blender
