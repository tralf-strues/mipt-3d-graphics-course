add_library(stb_image)

set(STB_IMAGE_INCLUDE_DIR include)
set(STB_IMAGE_SOURCE_DIR src)

target_include_directories(stb_image
  PUBLIC
    ${STB_IMAGE_INCLUDE_DIR}
  )

target_sources(stb_image
  PUBLIC
    ${STB_IMAGE_INCLUDE_DIR}/stb_image/stb_image.h
  PRIVATE
    ${STB_IMAGE_SOURCE_DIR}/stb_image.cpp
  )
