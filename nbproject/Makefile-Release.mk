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
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/InfoSheet.o \
	${OBJECTDIR}/_ext/1928089307/Mesh.o \
	${OBJECTDIR}/_ext/1296285299/main.o \
	${OBJECTDIR}/_ext/893437282/main.o \
	${OBJECTDIR}/_ext/2088469020/ctNode.o \
	${OBJECTDIR}/Feature.o \
	${OBJECTDIR}/CriticalPoint.o \
	${OBJECTDIR}/_ext/1008408782/ctQueue.o \
	${OBJECTDIR}/FeatureWeights.o \
	${OBJECTDIR}/_ext/1579105866/trilinear.o \
	${OBJECTDIR}/GeoSequence.o \
	${OBJECTDIR}/ViewPathClusterFinder.o \
	${OBJECTDIR}/MetaballsVol4D.o \
	${OBJECTDIR}/TemporalChangeFeature.o \
	${OBJECTDIR}/CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.o \
	${OBJECTDIR}/_ext/2088469020/tourtre.o \
	${OBJECTDIR}/LoadedVol4D.o \
	${OBJECTDIR}/_ext/1008408782/tourtre.o \
	${OBJECTDIR}/_ext/1008408782/ctComponent.o \
	${OBJECTDIR}/ViewEvaluator.o \
	${OBJECTDIR}/_ext/893437282/Mesh.o \
	${OBJECTDIR}/TemporalChangeFeature2.o \
	${OBJECTDIR}/testOVAS.o \
	${OBJECTDIR}/FlyingSaucersVol4D.o \
	${OBJECTDIR}/_ext/1008408782/ctArc.o \
	${OBJECTDIR}/abstractFeature.o \
	${OBJECTDIR}/_ext/2088469020/ctArc.o \
	${OBJECTDIR}/_ext/1928089307/Data.o \
	${OBJECTDIR}/TopologyFeature.o \
	${OBJECTDIR}/OVASControl.o \
	${OBJECTDIR}/CMakeFiles/CompilerIdC/CMakeCCompilerId.o \
	${OBJECTDIR}/MovingAAElipsoid.o \
	${OBJECTDIR}/GeoPoint.o \
	${OBJECTDIR}/InfoData.o \
	${OBJECTDIR}/_ext/2088469020/ctComponent.o \
	${OBJECTDIR}/_ext/2088469020/ctBranch.o \
	${OBJECTDIR}/_ext/1008408782/ctNode.o \
	${OBJECTDIR}/_ext/1296285299/Mesh.o \
	${OBJECTDIR}/_ext/1008408782/ctBranch.o \
	${OBJECTDIR}/_ext/1391473104/main.o \
	${OBJECTDIR}/_ext/1928089307/main.o \
	${OBJECTDIR}/_ext/1296285299/Data.o \
	${OBJECTDIR}/FrameBuffer.o \
	${OBJECTDIR}/_ext/2088469020/ctNodeMap.o \
	${OBJECTDIR}/_ext/533639364/main.o \
	${OBJECTDIR}/GeoSphere.o \
	${OBJECTDIR}/AreaFeature.o \
	${OBJECTDIR}/Mesh.o \
	${OBJECTDIR}/_ext/1391473104/Mesh.o \
	${OBJECTDIR}/Analyser3D.o \
	${OBJECTDIR}/_ext/1579105866/main.o \
	${OBJECTDIR}/testRenderView.o \
	${OBJECTDIR}/ImplicitVolume4D.o \
	${OBJECTDIR}/_ext/533639364/trilinear.o \
	${OBJECTDIR}/PathVisualiser.o \
	${OBJECTDIR}/Analyser4D.o \
	${OBJECTDIR}/testVol4D.o \
	${OBJECTDIR}/Volume4D.o \
	${OBJECTDIR}/_ext/1008408782/ctNodeMap.o \
	${OBJECTDIR}/Data.o \
	${OBJECTDIR}/StepToParamConverter.o \
	${OBJECTDIR}/_ext/2088469020/ctQueue.o


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
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ovas

${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ovas: ${OBJECTFILES}
	${MKDIR} -p ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}
	${LINK.cc} -o ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ovas ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/InfoSheet.o: InfoSheet.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/InfoSheet.o InfoSheet.cpp

${OBJECTDIR}/_ext/1928089307/Mesh.o: ../woven/libtourtre_v15/libtourtre/examples/simple/src/Mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1928089307
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1928089307/Mesh.o ../woven/libtourtre_v15/libtourtre/examples/simple/src/Mesh.cpp

${OBJECTDIR}/_ext/1296285299/main.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/simple/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1296285299
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1296285299/main.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/simple/src/main.cpp

${OBJECTDIR}/_ext/893437282/main.o: ../woven/libtourtre_v15/libtourtre/examples/tiff/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/893437282
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/893437282/main.o ../woven/libtourtre_v15/libtourtre/examples/tiff/src/main.cpp

${OBJECTDIR}/_ext/2088469020/ctNode.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/ctNode.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2088469020
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2088469020/ctNode.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/ctNode.c

${OBJECTDIR}/Feature.o: Feature.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Feature.o Feature.cpp

${OBJECTDIR}/CriticalPoint.o: CriticalPoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CriticalPoint.o CriticalPoint.cpp

${OBJECTDIR}/_ext/1008408782/ctQueue.o: ../woven/libtourtre_v15/libtourtre/src/ctQueue.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008408782
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1008408782/ctQueue.o ../woven/libtourtre_v15/libtourtre/src/ctQueue.c

${OBJECTDIR}/FeatureWeights.o: FeatureWeights.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/FeatureWeights.o FeatureWeights.cpp

${OBJECTDIR}/_ext/1579105866/trilinear.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/trilinear/trilinear.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1579105866
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1579105866/trilinear.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/trilinear/trilinear.c

${OBJECTDIR}/GeoSequence.o: GeoSequence.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/GeoSequence.o GeoSequence.cpp

${OBJECTDIR}/ViewPathClusterFinder.o: ViewPathClusterFinder.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ViewPathClusterFinder.o ViewPathClusterFinder.cpp

${OBJECTDIR}/MetaballsVol4D.o: MetaballsVol4D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/MetaballsVol4D.o MetaballsVol4D.cpp

${OBJECTDIR}/TemporalChangeFeature.o: TemporalChangeFeature.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/TemporalChangeFeature.o TemporalChangeFeature.cpp

${OBJECTDIR}/CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.o: CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.cpp 
	${MKDIR} -p ${OBJECTDIR}/CMakeFiles/CompilerIdCXX
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.o CMakeFiles/CompilerIdCXX/CMakeCXXCompilerId.cpp

${OBJECTDIR}/_ext/2088469020/tourtre.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/tourtre.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2088469020
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2088469020/tourtre.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/tourtre.c

${OBJECTDIR}/LoadedVol4D.o: LoadedVol4D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/LoadedVol4D.o LoadedVol4D.cpp

${OBJECTDIR}/_ext/1008408782/tourtre.o: ../woven/libtourtre_v15/libtourtre/src/tourtre.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008408782
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1008408782/tourtre.o ../woven/libtourtre_v15/libtourtre/src/tourtre.c

${OBJECTDIR}/_ext/1008408782/ctComponent.o: ../woven/libtourtre_v15/libtourtre/src/ctComponent.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008408782
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1008408782/ctComponent.o ../woven/libtourtre_v15/libtourtre/src/ctComponent.c

${OBJECTDIR}/ViewEvaluator.o: ViewEvaluator.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ViewEvaluator.o ViewEvaluator.cpp

${OBJECTDIR}/_ext/893437282/Mesh.o: ../woven/libtourtre_v15/libtourtre/examples/tiff/src/Mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/893437282
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/893437282/Mesh.o ../woven/libtourtre_v15/libtourtre/examples/tiff/src/Mesh.cpp

${OBJECTDIR}/TemporalChangeFeature2.o: TemporalChangeFeature2.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/TemporalChangeFeature2.o TemporalChangeFeature2.cpp

${OBJECTDIR}/testOVAS.o: testOVAS.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/testOVAS.o testOVAS.cpp

${OBJECTDIR}/FlyingSaucersVol4D.o: FlyingSaucersVol4D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/FlyingSaucersVol4D.o FlyingSaucersVol4D.cpp

${OBJECTDIR}/_ext/1008408782/ctArc.o: ../woven/libtourtre_v15/libtourtre/src/ctArc.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008408782
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1008408782/ctArc.o ../woven/libtourtre_v15/libtourtre/src/ctArc.c

${OBJECTDIR}/abstractFeature.o: abstractFeature.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/abstractFeature.o abstractFeature.cpp

${OBJECTDIR}/_ext/2088469020/ctArc.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/ctArc.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2088469020
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2088469020/ctArc.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/ctArc.c

${OBJECTDIR}/_ext/1928089307/Data.o: ../woven/libtourtre_v15/libtourtre/examples/simple/src/Data.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1928089307
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1928089307/Data.o ../woven/libtourtre_v15/libtourtre/examples/simple/src/Data.cpp

${OBJECTDIR}/TopologyFeature.o: TopologyFeature.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/TopologyFeature.o TopologyFeature.cpp

${OBJECTDIR}/OVASControl.o: OVASControl.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/OVASControl.o OVASControl.cpp

${OBJECTDIR}/CMakeFiles/CompilerIdC/CMakeCCompilerId.o: CMakeFiles/CompilerIdC/CMakeCCompilerId.c 
	${MKDIR} -p ${OBJECTDIR}/CMakeFiles/CompilerIdC
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/CMakeFiles/CompilerIdC/CMakeCCompilerId.o CMakeFiles/CompilerIdC/CMakeCCompilerId.c

${OBJECTDIR}/MovingAAElipsoid.o: MovingAAElipsoid.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/MovingAAElipsoid.o MovingAAElipsoid.cpp

${OBJECTDIR}/GeoPoint.o: GeoPoint.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/GeoPoint.o GeoPoint.cpp

${OBJECTDIR}/InfoData.o: InfoData.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/InfoData.o InfoData.cpp

${OBJECTDIR}/_ext/2088469020/ctComponent.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/ctComponent.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2088469020
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2088469020/ctComponent.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/ctComponent.c

${OBJECTDIR}/_ext/2088469020/ctBranch.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/ctBranch.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2088469020
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2088469020/ctBranch.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/ctBranch.c

${OBJECTDIR}/_ext/1008408782/ctNode.o: ../woven/libtourtre_v15/libtourtre/src/ctNode.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008408782
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1008408782/ctNode.o ../woven/libtourtre_v15/libtourtre/src/ctNode.c

${OBJECTDIR}/_ext/1296285299/Mesh.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/simple/src/Mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1296285299
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1296285299/Mesh.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/simple/src/Mesh.cpp

${OBJECTDIR}/_ext/1008408782/ctBranch.o: ../woven/libtourtre_v15/libtourtre/src/ctBranch.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008408782
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1008408782/ctBranch.o ../woven/libtourtre_v15/libtourtre/src/ctBranch.c

${OBJECTDIR}/_ext/1391473104/main.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/tiff/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1391473104
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1391473104/main.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/tiff/src/main.cpp

${OBJECTDIR}/_ext/1928089307/main.o: ../woven/libtourtre_v15/libtourtre/examples/simple/src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1928089307
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1928089307/main.o ../woven/libtourtre_v15/libtourtre/examples/simple/src/main.cpp

${OBJECTDIR}/_ext/1296285299/Data.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/simple/src/Data.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1296285299
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1296285299/Data.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/simple/src/Data.cpp

${OBJECTDIR}/FrameBuffer.o: FrameBuffer.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/FrameBuffer.o FrameBuffer.cpp

${OBJECTDIR}/_ext/2088469020/ctNodeMap.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/ctNodeMap.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2088469020
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2088469020/ctNodeMap.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/ctNodeMap.c

${OBJECTDIR}/_ext/533639364/main.o: ../woven/libtourtre_v15/libtourtre/examples/trilinear/main.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/533639364
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/533639364/main.o ../woven/libtourtre_v15/libtourtre/examples/trilinear/main.c

${OBJECTDIR}/GeoSphere.o: GeoSphere.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/GeoSphere.o GeoSphere.cpp

${OBJECTDIR}/AreaFeature.o: AreaFeature.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/AreaFeature.o AreaFeature.cpp

${OBJECTDIR}/Mesh.o: Mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Mesh.o Mesh.cpp

${OBJECTDIR}/_ext/1391473104/Mesh.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/tiff/src/Mesh.cpp 
	${MKDIR} -p ${OBJECTDIR}/_ext/1391473104
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1391473104/Mesh.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/tiff/src/Mesh.cpp

${OBJECTDIR}/Analyser3D.o: Analyser3D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Analyser3D.o Analyser3D.cpp

${OBJECTDIR}/_ext/1579105866/main.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/trilinear/main.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1579105866
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1579105866/main.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/examples/trilinear/main.c

${OBJECTDIR}/testRenderView.o: testRenderView.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/testRenderView.o testRenderView.cpp

${OBJECTDIR}/ImplicitVolume4D.o: ImplicitVolume4D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/ImplicitVolume4D.o ImplicitVolume4D.cpp

${OBJECTDIR}/_ext/533639364/trilinear.o: ../woven/libtourtre_v15/libtourtre/examples/trilinear/trilinear.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/533639364
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/533639364/trilinear.o ../woven/libtourtre_v15/libtourtre/examples/trilinear/trilinear.c

${OBJECTDIR}/PathVisualiser.o: PathVisualiser.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/PathVisualiser.o PathVisualiser.cpp

${OBJECTDIR}/Analyser4D.o: Analyser4D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Analyser4D.o Analyser4D.cpp

${OBJECTDIR}/testVol4D.o: testVol4D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/testVol4D.o testVol4D.cpp

${OBJECTDIR}/Volume4D.o: Volume4D.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Volume4D.o Volume4D.cpp

${OBJECTDIR}/_ext/1008408782/ctNodeMap.o: ../woven/libtourtre_v15/libtourtre/src/ctNodeMap.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/1008408782
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/1008408782/ctNodeMap.o ../woven/libtourtre_v15/libtourtre/src/ctNodeMap.c

${OBJECTDIR}/Data.o: Data.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/Data.o Data.cpp

${OBJECTDIR}/StepToParamConverter.o: StepToParamConverter.cpp 
	${MKDIR} -p ${OBJECTDIR}
	${RM} $@.d
	$(COMPILE.cc) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/StepToParamConverter.o StepToParamConverter.cpp

${OBJECTDIR}/_ext/2088469020/ctQueue.o: ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/ctQueue.c 
	${MKDIR} -p ${OBJECTDIR}/_ext/2088469020
	${RM} $@.d
	$(COMPILE.c) -O2 -MMD -MP -MF $@.d -o ${OBJECTDIR}/_ext/2088469020/ctQueue.o ../woven/libtourtre_v15/libtourtre/_darcs/pristine/src/ctQueue.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ${CND_DISTDIR}/${CND_CONF}/${CND_PLATFORM}/ovas

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
