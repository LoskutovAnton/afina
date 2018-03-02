file(REMOVE_RECURSE
  "runNetworkTests.pdb"
  "runNetworkTests"
)

# Per-language clean rules from dependency scanning.
foreach(lang CXX)
  include(CMakeFiles/runNetworkTests.dir/cmake_clean_${lang}.cmake OPTIONAL)
endforeach()
