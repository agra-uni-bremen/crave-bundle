find_package(Boost)
include_directories( ${crave_SOURCE_DIR}/src ${metaSMT_INCLUDE_DIR} ${Boost_INCLUDE_DIRS})

find_library(PTHREAD pthread)

add_executable(ex1_seed_dist ex1_seed_dist/main.cpp)
target_link_libraries(ex1_seed_dist crave ${PTHREAD} )

add_executable(ex2_constr_ref ex2_constr_ref/main.cpp)
target_link_libraries(ex2_constr_ref crave ${PTHREAD} )

add_executable(ex3_inh_soft_next ex3_inh_soft_next/main.cpp)
target_link_libraries(ex3_inh_soft_next crave ${PTHREAD} )

add_executable(ex4_constr_mng ex4_constr_mng/main.cpp)
target_link_libraries(ex4_constr_mng crave ${PTHREAD} )

add_executable(ex5_vec_constr ex5_vec_constr/main.cpp)
target_link_libraries(ex5_vec_constr crave ${PTHREAD} )

add_executable(ex6_inline_gen ex6_inline_gen/main.cpp)
target_link_libraries(ex6_inline_gen crave ${PTHREAD} )

add_executable(ex7_randv_enum ex7_randv_enum/main.cpp)
target_link_libraries(ex7_randv_enum crave ${PTHREAD} )

if(SystemC_FOUND)
  include_directories(crave/src metaSMT/src)
  add_subdirectory(ALU)
endif(SystemC_FOUND)
