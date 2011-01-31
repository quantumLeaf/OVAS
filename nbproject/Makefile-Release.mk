#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/GeoSequence.o \
	${OBJECTDIR}/Feature.o \
	${OBJECTDIR}/MetaballsVol4D.o \
	${OBJECTDIR}/CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.o \
	${OBJECTDIR}/testOVAS.o \
	${OBJECTDIR}/abstractFeature.o \
	${OBJECTDIR}/CMakeFiles/CompilerIdC/CMakeCCompilerId.o \
	${OBJECTDIR}/GeoPoint.o \
	${OBJECTDIR}/FrameBuffer.o \
	${OBJECTDIR}/GeoSphere.o \
	${OBJECTDIR}/AreaFeature.o \
	${OBJECTDIR}/Analyser3D.o \
	${OBJECTDIR}/Analyser4D.o \
	${OBJECTDIR}/ImplicitVolume4D.o \
	${OBJECTDIR}/Volume4D.o \
	${OBJECTDIR}/StepToParamConverter.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-Release.mk dist/Release/GNU-Linux-x86/ovas

dist/Release/GNU-Linux-x86/ovas: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ovas ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/GeoSequence.o: GeoSequence.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/GeoSequence.o GeoSequence.cpp

${OBJECTDIR}/Feature.o: Feature.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Feature.o Feature.cpp

${OBJECTDIR}/MetaballsVol4D.o: MetaballsVol4D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/MetaballsVol4D.o MetaballsVol4D.cpp

${OBJECTDIR}/CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.o: CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.cpp 
	${MKDIR} -p ${OBJECTDIR}/CMakeFiles/CompilerIdCXX
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.o CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.cpp

${OBJECTDIR}/testOVAS.o: testOVAS.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/testOVAS.o testOVAS.cpp

${OBJECTDIR}/abstractFeature.o: abstractFeature.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/abstractFeature.o abstractFeature.cpp

${OBJECTDIR}/CMakeFiles/CompilerIdC/CMakeCCompilerId.o: CMakeFiles/CompilerIdC/CMakeCCompilerId.c 
	${MKDIR} -p ${OBJECTDIR}/CMakeFiles/CompilerIdC
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CMakeFiles/CompilerIdC/CMakeCCompilerId.o CMakeFiles/CompilerIdC/CMakeCCompilerId.c

${OBJECTDIR}/GeoPoint.o: GeoPoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/GeoPoint.o GeoPoint.cpp

${OBJECTDIR}/FrameBuffer.o: FrameBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/FrameBuffer.o FrameBuffer.cpp

${OBJECTDIR}/GeoSphere.o: GeoSphere.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/GeoSphere.o GeoSphere.cpp

${OBJECTDIR}/AreaFeature.o: AreaFeature.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AreaFeature.o AreaFeature.cpp

${OBJECTDIR}/Analyser3D.o: Analyser3D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Analyser3D.o Analyser3D.cpp

${OBJECTDIR}/Analyser4D.o: Analyser4D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Analyser4D.o Analyser4D.cpp

${OBJECTDIR}/ImplicitVolume4D.o: ImplicitVolume4D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ImplicitVolume4D.o ImplicitVolume4D.cpp

${OBJECTDIR}/Volume4D.o: Volume4D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Volume4D.o Volume4D.cpp

${OBJECTDIR}/StepToParamConverter.o: StepToParamConverter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/StepToParamConverter.o StepToParamConverter.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/ovas

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
