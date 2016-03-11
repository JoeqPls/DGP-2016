APPNAME = 02-Registration
ROOTDIR = .
TEMPLATE = app
TARGET = $$APPNAME
VERISON = 1.0

# set compiler
QMAKE_CXX = g++
QMAKE_LINK = $$QMAKE_CXX

# set glut directories
GLUT_INCLUDE_DIR =
GLUT_LIB_DIR =

INCDIR = .
SRCDIR = .
OPENMESHDIR = ../..
ANNDIR = ../..

INCLUDEPATH +=\
	$$INCDIR \
	$$OPENMESHDIR \
	$$ANNDIR \
	# GLUT
	GLUT_INCLUDE_DIR
	
CONFIG = \
	release\
	warn_on\
	opengl
	
unix:macx {
	QMAKE_CXXFLAGS += -DARCH_DARWIN
	LIBS += -framework GLUT
}

unix:!macx {
INCLUDEPATH +=\
	GLUT_INCLUDE_DIR

LIBS += \
	# GLUT
	-L$$GLUT_LIB_DIR				\
	-Wl,-rpath,$$GLUT_LIB_DIR		\
	-lglut			
}
													
	
TEMP_DIR = $$ROOTDIR/tmp
OBJECTS_DIR = $$TEMP_DIR/obj
MOC_DIR = $$TEMP_DIR/moc

HEADERS += \


SOURCES += \
		\ # OPENMESH
		$$OPENMESHDIR/OpenMesh/Core/IO/BinaryHelper.cc                   \
		$$OPENMESHDIR/OpenMesh/Core/Utils/Endian.cc                      \
		$$OPENMESHDIR/OpenMesh/Tools/Smoother/SmootherT.cc               \
		$$OPENMESHDIR/OpenMesh/Tools/VDPM/VHierarchy.cc \
		$$OPENMESHDIR/OpenMesh/Core/IO/IOManager.cc \
		$$OPENMESHDIR/OpenMesh/Core/Utils/SingletonT.cc \
		$$OPENMESHDIR/OpenMesh/Tools/Utils/MeshCheckerT.cc \
		$$OPENMESHDIR/OpenMesh/Tools/VDPM/VHierarchyNodeIndex.cc \
		#$$OPENMESHDIR/OpenMesh/Core/IO/OMFormat.cc \
		$$OPENMESHDIR/OpenMesh/Tools/Decimater/DecimaterT.cc  \
		$$OPENMESHDIR/OpenMesh/Tools/Utils/Progress.cc \
		$$OPENMESHDIR/OpenMesh/Tools/VDPM/VHierarchyWindow.cc \
		$$OPENMESHDIR/OpenMesh/Core/Mesh/PolyMeshT.cc \
		$$OPENMESHDIR/OpenMesh/Tools/Decimater/ModProgMeshT.cc \
		$$OPENMESHDIR/OpenMesh/Tools/Utils/StripifierT.cc \
		$$OPENMESHDIR/OpenMesh/Tools/VDPM/ViewingParameters.cc \
		$$OPENMESHDIR/OpenMesh/Core/Mesh/TriMeshT.cc \
		$$OPENMESHDIR/OpenMesh/Tools/Decimater/ModQuadricT.cc \
		$$OPENMESHDIR/OpenMesh/Tools/Utils/Timer.cc \
		$$OPENMESHDIR/OpenMesh/Core/System/omstream.cc \
		$$OPENMESHDIR/OpenMesh/Tools/Smoother/JacobiLaplaceSmootherT.cc \
		$$OPENMESHDIR/OpenMesh/Tools/Utils/getopt.cc \
		$$OPENMESHDIR/OpenMesh/Core/Utils/BaseProperty.cc \
		$$OPENMESHDIR/OpenMesh/Tools/Smoother/LaplaceSmootherT.cc \
		$$OPENMESHDIR/OpenMesh/Tools/VDPM/VFront.cc \
		$$OPENMESHDIR/OpenMesh/Core/IO/reader/BaseReader.cc \
		$$OPENMESHDIR/OpenMesh/Core/IO/reader/OFFReader.cc \
		$$OPENMESHDIR/OpenMesh/Core/IO/reader/STLReader.cc \
		$$OPENMESHDIR/OpenMesh/Core/IO/writer/OBJWriter.cc \
		#$$OPENMESHDIR/OpenMesh/Core/IO/writer/OMWriter.cc \
		$$OPENMESHDIR/OpenMesh/Core/IO/reader/OBJReader.cc \
		#$$OPENMESHDIR/OpenMesh/Core/IO/reader/OMReader.cc \
		$$OPENMESHDIR/OpenMesh/Core/IO/writer/BaseWriter.cc \
		$$OPENMESHDIR/OpenMesh/Core/IO/writer/OFFWriter.cc \
		$$OPENMESHDIR/OpenMesh/Core/IO/writer/STLWriter.cc \
		\
		# ANN
		$$ANNDIR/ANN/ANN.cpp \
		$$ANNDIR/ANN/bd_fix_rad_search.cpp \
		$$ANNDIR/ANN/bd_pr_search.cpp \
		$$ANNDIR/ANN/bd_search.cpp \
		$$ANNDIR/ANN/bd_tree.cpp \
		$$ANNDIR/ANN/brute.cpp \
		$$ANNDIR/ANN/kd_dump.cpp \
		$$ANNDIR/ANN/kd_fix_rad_search.cpp \
		$$ANNDIR/ANN/kd_pr_search.cpp \
		$$ANNDIR/ANN/kd_search.cpp \
		$$ANNDIR/ANN/kd_split.cpp \
		$$ANNDIR/ANN/kd_tree.cpp \
		$$ANNDIR/ANN/kd_util.cpp \
		$$ANNDIR/ANN/perf.cpp \
		\ # main files
                GlutViewer.cc \
                GlutExaminer.cc \
                RegistrationViewer.cc \ 
		Transformation.cc \
		ClosestPoint.cc \
		Registration.cc \
                registrationview.cc

