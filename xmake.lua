add_rules("mode.debug", "mode.release")

set_version("0.1.6", {build = "%Y%m%d%H%M"})

set_languages("c++20")
-- add_requires("muslcc")
-- set_toolchains("@muslcc")

add_requires("opencv", {system = true})
add_requires("eigen", {system = false})
add_requires("fmt", {system = false})
add_requires("spdlog", {system = false}) 
 
target("run")
    set_kind("binary")
    add_includedirs("include")
    add_files("src/*.cpp")
    add_packages("opencv")
    add_packages("eigen")
    add_packages("fmt")
    add_packages("spdlog")