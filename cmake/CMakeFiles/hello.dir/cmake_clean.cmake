file(REMOVE_RECURSE
  "hello"
  "hello.pdb"
)

# Per-language clean rules from dependency scanning.
foreach(lang C)
  include(CMakeFiles/hello.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
