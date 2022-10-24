function(DOWNLOAD_SDK type platform version suffix download_dir)
    # Specify the binary distribution type and download directory.
    string(TOUPPER ${suffix} SUFFIX_UPPER)
    set(SDK_DISTRIBUTION "${type}_for_${platform}${version}${suffix}")
    message(STATUS "SDK_DISTRIBUTION ${SDK_DISTRIBUTION}")
    set(SDK_DOWNLOAD_DIR "${download_dir}")

    # The location where we expect the extracted binary distribution.
    set(SDK_ROOT "${SDK_DOWNLOAD_DIR}/${type}_for_${platform}${SUFFIX_UPPER}" CACHE INTERNAL "SDK_ROOT")

    # Download and/or extract the binary distribution if necessary.
    if (NOT IS_DIRECTORY "${SDK_ROOT}")
        set(SDK_DOWNLOAD_FILENAME "${SDK_DISTRIBUTION}.zip")
        set(SDK_DOWNLOAD_PATH "${SDK_DOWNLOAD_DIR}/${SDK_DOWNLOAD_FILENAME}")
        if (NOT EXISTS "${SDK_DOWNLOAD_PATH}")
            set(SDK_DOWNLOAD_URL "https://download.agora.io/sdk/release/${SDK_DOWNLOAD_FILENAME}")
            string(REPLACE "+" "%2B" SDK_DOWNLOAD_URL_E
            SCAPED ${SDK_DOWNLOAD_URL})

            # Download the binary distribution and verify the hash.
            message(STATUS "Downloading ${SDK_DOWNLOAD_PATH}...")
            file(
                    DOWNLOAD "${SDK_DOWNLOAD_URL_ESCAPED}" "${SDK_DOWNLOAD_PATH}"
                    SHOW_PROGRESS
            )
        endif ()

        # Extract the binary distribution.
        message(STATUS "Extracting ${SDK_DOWNLOAD_PATH}...")
        execute_process(
                COMMAND ${CMAKE_COMMAND} -E tar xzf "${SDK_DOWNLOAD_DIR}/${SDK_DOWNLOAD_FILENAME}"
                WORKING_DIRECTORY ${SDK_DOWNLOAD_DIR}
        )
    endif ()
endfunction()

function(DOWNLOAD_SDK_BY_URL download_url download_dir)
    # Specify the binary distribution type and download directory.
    STRING(REGEX REPLACE ".+/(.+)\\..*" "\\1" SDK_DISTRIBUTION ${download_url})
    message(STATUS "SDK_DISTRIBUTION ${SDK_DISTRIBUTION}")
    set(SDK_DOWNLOAD_DIR "${download_dir}")
    STRING(REGEX REPLACE ".*for_[A-Za-z]*_(.+)" "\\1" SDK_SUFFIX ${SDK_DISTRIBUTION})
    message(STATUS "SDK_SUFFIX ${SDK_SUFFIX}")

    # The location where we expect the extracted binary distribution.
    set(SDK_ROOT "${SDK_DOWNLOAD_DIR}/${SDK_TYPE}_for_${IRIS_PLATFORM}_${SDK_SUFFIX}" CACHE INTERNAL "SDK_ROOT")

    # Download and/or extract the binary distribution if necessary.
    if (NOT IS_DIRECTORY "${SDK_ROOT}")
        set(SDK_DOWNLOAD_FILENAME "${SDK_DISTRIBUTION}.zip")
        set(SDK_DOWNLOAD_PATH "${SDK_DOWNLOAD_DIR}/${SDK_DOWNLOAD_FILENAME}")
        if (NOT EXISTS "${SDK_DOWNLOAD_PATH}")
            set(SDK_DOWNLOAD_URL "${download_url}")
            string(REPLACE "+" "%2B" SDK_DOWNLOAD_URL_ESCAPED ${SDK_DOWNLOAD_URL})

            # Download the binary distribution and verify the hash.
            message(STATUS "Downloading ${SDK_DOWNLOAD_PATH}...")
            file(
                    DOWNLOAD "${SDK_DOWNLOAD_URL_ESCAPED}" "${SDK_DOWNLOAD_PATH}"
                    SHOW_PROGRESS
            )
        endif ()

        # Extract the binary distribution.
        message(STATUS "Extracting ${SDK_DOWNLOAD_PATH}...")
        execute_process(
                COMMAND ${CMAKE_COMMAND} -E tar xzf "${SDK_DOWNLOAD_DIR}/${SDK_DOWNLOAD_FILENAME}"
                WORKING_DIRECTORY ${SDK_DOWNLOAD_DIR}
        )
    endif ()
endfunction()
