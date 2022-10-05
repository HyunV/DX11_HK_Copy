cd..
cd..
xcopy .\MyAR41Engine\Include\*.h .\Engine\Include\ /d /s /y
xcopy .\MyAR41Engine\Include\*.inl .\Engine\Include\ /d /s /y
xcopy .\MyAR41Engine\Include\*.hpp .\Engine\Include\ /d /s /y
xcopy .\MyAR41Engine\Bin\*.* .\Engine\Bin\ /d /s /y  /exclude:Exclude.txt
xcopy .\MyAR41Engine\Bin\*.* .\MyAR41MapEditor\Bin\ /d /s /y /exclude:Exclude.txt
xcopy .\MyAR41Engine\Bin\*.* .\MyClient2D\Bin\ /d /s /y /exclude:Exclude.txt