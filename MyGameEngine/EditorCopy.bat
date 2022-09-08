REM 프로젝트 속성->빌드이벤트->빌드 후 이벤트 명령어 참고
cd..
cd..
xcopy .\MyAR41MapEditor\Include\GameObject\*.* .\MyClient2D\Include\GameObject\ /d /s /y
xcopy .\MyAR41MapEditor\Include\Scene\*.* .\MyClient2D\Include\Scene\ /d /s /y /exclude:EditorExclude.txt

xcopy .\MyAR41MapEditor\Bin\*.* .\MyClient2D\Bin\ /d /s /y /exclude:Exclude.txt