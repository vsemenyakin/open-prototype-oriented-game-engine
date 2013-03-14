# ========================
#  Arguments:
#   [1] = Project root
#
#  Activites:
#   1. Bundle creation;
# ========================



# ==========
#  Imports

# "sys" - needs for getting command line arguments
import sys

# "os.path" - needs for operations with path
import os;

import shutil

# ===========
#  Functions

def copyFolderContents(inSourceFolder, inDestinationFolder, inIgnore = None, inDoReplacement = True):

    # File existing handling
    if False == os.path.exists(inSourceFolder):
        return False

    if False == os.path.exists(inDestinationFolder):
        return False

    # Get source folder members name and create ignore list for this folder
    theSourceFolderMemberNames = os.listdir(inSourceFolder)
    theIgnoreList = inIgnore(inSourceFolder, theSourceFolderMemberNames)
    
    for theSourceFolderMemberName in theSourceFolderMemberNames:

        # If member is on ignore list - do nothing
        if theSourceFolderMemberName in theIgnoreList:
            continue

        # Create source and destination member paths
        theDestinationMemberPath = os.path.join(inDestinationFolder, theSourceFolderMemberName)
        theSourceMemberPath = os.path.join(inSourceFolder, theSourceFolderMemberName)

        # If <inDoOverwriting> argument is True - replace destination member
        if True == os.path.exists(theDestinationMemberPath):
            if True == inDoReplacement:
                if True == os.path.isdir(theDestinationMemberPath):
                    shutil.rmtree(theDestinationMemberPath)
                else:
                    os.remove(theDestinationMemberPath)
            else:
                continue
        
        if True == os.path.isdir(theSourceMemberPath):
            shutil.copytree(theSourceMemberPath, theDestinationMemberPath, ignore = inIgnore)
        else:
            shutil.copy2(theSourceMemberPath, theDestinationMemberPath)


def svnIgnoreFunction(inFolder, inMemberNames):
    theIgnoreList = []
    
    for theMemberName in inMemberNames:
       thePath = os.path.join(inFolder, theMemberName)
       print(thePath)

       if os.path.isdir(thePath):
           if theMemberName == ".svn":
               theIgnoreList.append(theMemberName)
    return theIgnoreList

# -------------------------
#  Script starting verbose

print("Post build script started...")


# -----------
#  Set paths

# Getting project root
theProjectRootPath = ""

if len(sys.argv) < 1:
    print("ERROR: The first argument of script should be the project root path")
    sys.exit(1)

theProjectRootPath = sys.argv[1]

# Creating resources path variables
theBuildingProductPath = os.path.join(theProjectRootPath, "Debug")

theBundleResourcesPath = os.path.join(theProjectRootPath, "resources", "_bundle")
theSystemResourcesPath = os.path.join(theProjectRootPath, "resources", "_system")

# Creating scripts path variables
thePreBuildScriptsPath = os.path.join(theProjectRootPath, "scripts", "pre_build_sciprts")


# ----------------------
#  Build bundle actions

print("Start coping bundle resources...")

if False == copyFolderContents(theBundleResourcesPath, theBuildingProductPath, inIgnore = svnIgnoreFunction):
    print("ERROR: Error while coping bundle resources")
    sys.exit(1)

sys.exit(0)
