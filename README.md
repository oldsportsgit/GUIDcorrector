# GUIDcorrector

## Why?
Because when you decompile a unity game things like TMPro also get decompiled and decompilations aren't perfect at all but you can get TMPro in the package manager so you don't have to 
modify the decompiled package's code, shaders or whatever in order to make it work you can just use this GUID corrector which changes the GUIDs from the decompiled package to the one you got
from the package manager or whatever you got it.

## wtf is a "guid"?
a (G)lobally (U)nique (ID)entifier is a 128-bit text string that represents an identification (ID) unity uses this in their *.meta files so that they know what is what

## how it works
if we change this let's say we have
this guid (gb375d2c421da9a141a06fc1e9774eae5) in a *.meta file called "textmeshpro" from a decompiled package and (446635c639a68754da00264d9ac02476) also in a *.meta file called "textmeshpro.cs" 
from TMPro which we got from package manager and the whole project uses (gb375d2c421da9a141a06fc1e9774eae5) instead of the **actual** (446635c639a68754da00264d9ac02476) right? what this guid corrector does
is it goes through the decompiled package gets the guids in this case (gb375d2c421da9a141a06fc1e9774eae5) and finds another *.meta file with the same name in the "actual package" folder and retrieves (446635c639a68754da00264d9ac02476) next it finds all the places where "gb375d2c421da9a141a06fc1e9774eae5" occures and replaces it with (446635c639a68754da00264d9ac02476)

## Instructions

DecompiledPackagePath: The path for a decompiled package which is usually in "\Assets\Scripts\".

ActualPackagePath: The path where the actual package is that usually being "\Library\PackageCache\".

UnityProjectPath: Path of the unity project's "Assets" folder "\Assets\".

just download & run the program run it input the paths press enter and wait after it finishes you're done.
 
