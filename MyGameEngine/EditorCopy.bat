REM ������Ʈ �Ӽ�->�����̺�Ʈ->���� �� �̺�Ʈ ��ɾ� ����
cd..
cd..
xcopy .\MyAR41MapEditor\Include\GameObject\*.* .\MyClient2D\Include\GameObject\ /d /s /y
xcopy .\MyAR41MapEditor\Include\Scene\*.* .\MyClient2D\Include\Scene\ /d /s /y /exclude:EditorExclude.txt
xcopy .\MyAR41MapEditor\Include\UI\*.* .\MyClient2D\Include\UI\ /d /s /y /exclude:EditorExclude.txt
xcopy .\MyAR41MapEditor\Include\Setting\*.* .\MyClient2D\Include\Setting\ /d /s /y /exclude:EditorExclude.txt

xcopy .\MyAR41MapEditor\Bin\*.* .\MyClient2D\Bin\ /d /s /y /exclude:Exclude.txt