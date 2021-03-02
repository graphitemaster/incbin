# When I used INCBIN with cmake I have an error like this:
#   "C:\Users\UserName\AppData\Local\Temp\ccgFslxv.s: Assembler messages:"
#   "C:\Users\UserName\AppData\Local\Temp\ccgFslxv.s:2549: Error: file not found: FileName.txt" .
#
# This happens because the compiler cannot find the file in the build directory.
# With this macro you can automatically copy used files with a template [filename].incbin.[file extension]
# from directory [input_dir_absolute_path] to directory [output_dir_absolute_path].
# Сopied files will looks like [filename].[file extension].
#
# Usage:
#   1) move_incbin_to_destination([input_dir_absolute_path] [output_dir_absolute_path])
#   This copy files from [input_dir_absolute_path] to [output_dir_absolute_path] and remove ".incbin" from them names.
#   2) move_incbin_to_destination([input_dir_absolute_path] [output_dir_absolute_path] RECURSE)
#   This copy files from [input_dir_absolute_path]/[recursive all child folders] to
#       [output_dir_absolute_path]/[recursive all child folders from input dir] and remove ".incbin" from them names.
#
# Typical usage is (including quotes):
#   move_incbin_to_destination( "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_CURRENT_BINARY_DIR}" RECURSE)
# You can find examples in folder "test" in the repository https://github.com/graphitemaster/incbin

MACRO(move_incbin_to_destination input_dir_absolute_path output_dir_absolute_path)
set(RECURSE_FLAG "OFF")

if(${ARGC} EQUAL 3)
    if(${ARGV2} STREQUAL RECURSE)
        set(RECURSE_FLAG ON)
    else()
        message(FATAL_ERROR "Unknow parameter ${ARGV2}")
    endif()
endif(${ARGC} EQUAL 3)

if(${RECURSE_FLAG} STREQUAL "ON")
    message("MOVE_INCBIN_TO_DESTINATION RECURSE from folder ${input_dir_absolute_path}")
    file(GLOB_RECURSE INCBIN_FILES ${input_dir_absolute_path}/*.incbin*)
else()
    message("MOVE_INCBIN_TO_DESTINATION from folder ${input_dir_absolute_path}")
    file(GLOB INCBIN_FILES ${input_dir_absolute_path}/*.incbin*)
endif()

foreach(INCBIN_FILE ${INCBIN_FILES})

string(REGEX REPLACE "\\.incbin\\." "." NORMAL_FILE ${INCBIN_FILE})

string(REPLACE
    ${input_dir_absolute_path}
    ${output_dir_absolute_path}
    NORMAL_FILE
    ${NORMAL_FILE})

message("\r\n"
    "    ${INCBIN_FILE} ==>\r\n"
    "    ${NORMAL_FILE}")

configure_file(${INCBIN_FILE} ${NORMAL_FILE} COPYONLY)
endforeach()

message("End of MOVE_INCBIN_TO_DESTINATION\r\n")
ENDMACRO()
