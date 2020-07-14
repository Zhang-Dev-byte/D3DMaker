cmake_minimum_required(VERSION 3.15)

file(GLOB D3DMAKER_SRC
    "src/**.h"
    "src/**.cpp"
	"src/D3DMaker/**.h"
    "src/D3DMaker/**.cpp"
)

add_library(D3DMaker ${D3DMAKER_SRC})