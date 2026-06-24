<!-- Parent: ../AGENTS.md -->
<!-- Generated: 2026-06-25 | Updated: 2026-06-25 -->

# imbuf - Image Buffer Library

Image buffer library handling image loading, saving, color management, filtering, and format conversion. Public API uses the `IMB_` prefix. Supports many image formats.

## Subdirectories

| Directory | Description |
|-----------|-------------|
| `intern/` | Core image buffer implementation and format codecs |
| `movie/` | Movie/video file handling (FFmpeg integration) |
| `opencolorio/` | OpenColorIO color management integration |
| `tests/` | Unit tests |

## Key Files

| File | Description |
|------|-------------|
| `IMB_imbuf.hh` | Main image buffer API - alloc, load, save, manipulate |
| `IMB_imbuf_types.hh` | Image buffer data types (ImBuf struct) |
| `IMB_imbuf_enums.h` | Image buffer enumerations |
| `IMB_colormanagement.hh` | Color management - OCIO color spaces, transforms |
| `IMB_interp.hh` | Image interpolation (bilinear, bicubic sampling) |
| `IMB_metadata.hh` | Image metadata read/write |
| `IMB_moviecache.hh` | Movie frame caching system |
| `IMB_openexr.hh` | OpenEXR specific utilities |
| `IMB_thumbs.hh` | Thumbnail generation for images |
| `CMakeLists.txt` | Build configuration |

## Supported Formats (in intern/)

- **Raster**: BMP, PNG, JPEG, JPEG2000, Targa, TIFF, PSD, WebP, HDR, DPX, Cineon, IRIS, SVG, DDS
- **HDR/Linear**: OpenEXR, HDR, DPX, Cineon
- **Video**: FFmpeg-based movie handling (movie/)

## Common Patterns

- `ImBuf` is the central data structure holding pixel data and metadata
- Color management pipeline uses OpenColorIO (opencolorio/) for color space transforms
- Format codecs are registered via `IMB_filetype.hh` interface
- Filtering/interpolation operations in `intern/filter.cc`, `intern/interp.cc`

## For AI Agents

- `IMB_imbuf.hh` is the main entry point for all image operations
- Color management is critical - always go through `IMB_colormanagement.hh` APIs
- Format registration happens in `intern/filetype.cc` and `intern/module.cc`
- Thumbnail system (`IMB_thumbs.hh`, `intern/thumbs.cc`) generates previews for file browser
- GPU upload utilities in `intern/util_gpu.cc`
