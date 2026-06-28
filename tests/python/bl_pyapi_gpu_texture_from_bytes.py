# SPDX-FileCopyrightText: 2026 Blender Authors
#
# SPDX-License-Identifier: GPL-2.0-or-later

import unittest

import gpu


class GPUTextureFromBytesTests(unittest.TestCase):
    def test_from_bytes_exists(self):
        self.assertTrue(hasattr(gpu.texture, "from_bytes"))

    def test_rejects_short_buffer(self):
        with self.assertRaises(ValueError):
            gpu.texture.from_bytes(2, 2, b"\x00" * 15)

    def test_creates_rgba8_texture_from_bytes(self):
        pixels = bytes(
            [
                255,
                0,
                0,
                255,
                0,
                255,
                0,
                255,
                0,
                0,
                255,
                255,
                255,
                255,
                255,
                255,
            ]
        )

        tex = gpu.texture.from_bytes(2, 2, pixels, format="RGBA8", name="test_from_bytes")

        self.assertEqual(tex.width, 2)
        self.assertEqual(tex.height, 2)
        self.assertEqual(tex.format, "RGBA8")


if __name__ == "__main__":
    unittest.main()
