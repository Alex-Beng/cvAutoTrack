function(parse_version_file version_file)
    file(READ "${version_file}" version_file_content)
    string(STRIP "${version_file_content}" version_file_content)
    message(STATUS "当前编译版本: ${version_file_content}")
    string(REPLACE "." ";" version_content_list "${version_file_content}")
    list(GET version_content_list 0 version_major)
    list(GET version_content_list 1 version_minor)
    list(GET version_content_list 2 version_patch)
    set(VERSION_MAJOR ${version_major} PARENT_SCOPE)
    set(VERSION_MINOR ${version_minor} PARENT_SCOPE)
    set(VERSION_PATCH ${version_patch} PARENT_SCOPE)
endfunction(parse_version_file)

function(version_file_patch_update version_file)
    file(READ "${version_file}" version_file_content)
    string(REPLACE "." ";" version_content_list "${version_file_content}")
    list(GET version_content_list 0 version_major)
    list(GET version_content_list 1 version_minor)
    list(GET version_content_list 2 version_patch)
    math(EXPR version_patch "${version_patch} + 1")
    set(version_file_content "${version_major}.${version_minor}.${version_patch}")
    file(WRITE "${version_file}" "${version_file_content}")
endfunction(version_file_patch_update)

function(get_commit_hash hash_value)
find_package(Git QUIET)
if(NOT GIT_FOUND)
    message(STATUS "git not found, skip get_commit_hash")
    return()
endif()
execute_process(
    COMMAND ${GIT_EXECUTABLE} log -1 --pretty=format:%h
    OUTPUT_VARIABLE git_last_commit_hash
    OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
set(${hash_value} ${git_last_commit_hash} PARENT_SCOPE)
endfunction(get_commit_hash)

function(get_git_branch branch_name)
find_package(Git QUIET)
if(NOT GIT_FOUND)
    message(STATUS "git not found, skip get_git_branch")
    return()
endif()
execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --abbrev-ref HEAD
    OUTPUT_VARIABLE git_branch_name
    OUTPUT_STRIP_TRAILING_WHITESPACE ERROR_QUIET)
set(${branch_name} ${git_branch_name} PARENT_SCOPE)
endfunction(get_git_branch)


function(check_commit_hash_is_dirty is_dirty)
    execute_process(
        COMMAND git diff-index --quiet HEAD --
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE git_diff_index_result )
    if(git_diff_index_result EQUAL 0)
        set(${is_dirty} "false" PARENT_SCOPE)
    else()
        set(${is_dirty} "true" PARENT_SCOPE)
    endif()
endfunction(check_commit_hash_is_dirty)

function(auto_increment_version_file old_hash_file version_file)
    get_commit_hash(new_hash)
    message(STATUS "当前版本哈希: ${new_hash}")
    #check_commit_hash_is_dirty(is_dirty)
    if(is_dirty)
        message(STATUS "当前版本有修改, 不自动更新版本号")
        return()
    endif()
    if(EXISTS "${old_hash_file}")
        file(READ "${old_hash_file}" old_hash)
        message(STATUS "上次编译版本号: ${old_hash}")
        if(NOT "${old_hash}" STREQUAL "${new_hash}")
            message(STATUS "当前版本号与上次编译版本号不一致, 自动更新版本号")
            version_file_patch_update("${version_file}")
            file(WRITE "${old_hash_file}" "${new_hash}")
        endif()
    else()
        message(STATUS "当前版本号文件不存在, 自动更新版本号")
        version_file_patch_update("${version_file}")
        file(WRITE "${old_hash_file}" "${new_hash}")
    endif()
    
endfunction(auto_increment_version_file)
