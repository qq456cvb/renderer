# NaiveRenderer

A small **Monte Carlo path tracer** written from scratch in C++. It renders a hard-coded scene of spheres and a plane with physically-based light transport and displays the result in a native window (Win32 on Windows, X11 on Unix/Linux/macOS).

## Features

- **Unidirectional path tracing** (`Integrator::path_trace`) with:
  - **Next-event estimation** — explicit light sampling at each bounce, with shadow/occlusion tests.
  - **BSDF importance sampling** for the indirect bounce.
  - **Russian-roulette** path termination and a configurable max depth.
- **Material system** — a `BSDF` composed of `BXDF` lobes: `DIFFUSE`, `SPECULAR`, and a colored `Lambertian`.
- **Geometry** — `Sphere` and `Plane` shapes wrapped in `Primitive`s (shape + material + optional emitter).
- **Area lights** with radiance sampling.
- **Pinhole camera**.
- **Anti-aliasing** via 30 samples per pixel, tone-mapped by simple max-normalization.
- Linear algebra and RNG provided by [Armadillo](http://arma.sourceforge.net/) (`fvec3`, `arma::randu`, etc.).

The default scene (in `render()` in `main.cpp`) is 800×600 and contains a specular sphere, diffuse spheres, a blue Lambertian plane, and an emissive sphere acting as an area light.

## Code layout

| File(s) | Role |
| --- | --- |
| `main.cpp` | Scene construction + platform window/display (Win32 `SetDIBitsToDevice` / X11 `XPutImage`) |
| `integrator.{h,cpp}` | Path-tracing integrator and per-pixel sampling loop |
| `scene.{hpp,cpp}` | Scene container: intersection, occlusion, light list |
| `primitive.{hpp,cpp}` | Binds a shape to a material and optional light |
| `shape.h`, `sphere.{h,cpp}`, `plane.{h,cpp}` | Geometry and ray–shape intersection |
| `material.{hpp,cpp}`, `bsdf.{h,cpp}`, `bxdf.{h,cpp}`, `lambertian.{h,cpp}` | Material / BSDF model and lobes |
| `arealight.{h,cpp}`, `light.h` | Emitters and light sampling |
| `pinhole.{h,cpp}` | Pinhole camera ray generation |
| `ray.h`, `intersection.h`, `coord.{hpp,cpp}`, `montecarlo.hpp` | Ray/hit records, local coordinate frames, sampling utilities |

## Build & run

Requires a C++ compiler and **Armadillo**, plus the platform windowing library:

- **Linux/Unix:** X11 (`libX11`). Example:

```bash
g++ -std=c++14 renderer/*.cpp -o naive_renderer -larmadillo -lX11
./naive_renderer
```

- **Windows:** build the sources with MSVC (the Win32 `wWinMain` path is selected automatically); link against Armadillo.

A window opens and progressively shows the path-traced image.

## Notes

Prototype renderer — the scene is defined in code rather than loaded from a file, and the sample count / max depth are compile-time constants. A known TODO in the source is to move raw `new` pointers to smart pointers.
