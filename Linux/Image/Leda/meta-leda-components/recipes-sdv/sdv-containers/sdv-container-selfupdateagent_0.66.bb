# /********************************************************************************
# * Copyright (c) 2022 Contributors to the Eclipse Foundation
# *
# * See the NOTICE file(s) distributed with this work for additional
# * information regarding copyright ownership.
# *
# * This program and the accompanying materials are made available under the
# * terms of the Apache License 2.0 which is available at
# * https://www.apache.org/licenses/LICENSE-2.0
# *
# * SPDX-License-Identifier: Apache-2.0
# ********************************************************************************/

SUMMARY = "SDV Self Update Agent"
DESCRIPTION = "The self update agent (SUA) is a component responsible for the OS Update process."

inherit sdv-container-cache

SRC_URI += "file://README.txt \
            file://LICENSE"

# According to https://wiki.yoctoproject.org/wiki/License_Infrastructure_Interest_Group
LICENSE = "Apache-2.0"
LIC_FILES_CHKSUM = "file://${WORKDIR}/LICENSE;md5=3b83ef96387f14655fc854ddc3c6bd57"

# Define image to be pulled
SDV_IMAGE_REF="ghcr.io/eclipse-leda/leda-contrib-self-update-agent/self-update-agent"
SDV_IMAGE_TAG="build-66"

# Override container architecture. If not set, recipe tries autodetection for target machine architecture.
#CONTAINER_ARCH="arm64"

# Skip pre-caching of a container if target architecture does not exist
CONTAINER_SKIP_MISSING_ARCH="1"
