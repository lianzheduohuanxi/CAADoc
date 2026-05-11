' This command must be run with cscript /nologo
' It reads the standard input and
' - If no argument is specified: it outputs the full path.
' - If an argument is specified: it verifies if the full path is under the given path and it outputs the relative path.
' Pay attention: the path separator is "\".

Dim FileSystem
Set FileSystem = CreateObject("Scripting.FileSystemObject")

Set ObjArgs = WScript.Arguments
If objArgs.Count = 1 Then
  WsDir = objArgs(0) ' The given path is supposed to be an absolute one
  WsDir2 = WsDir & "\" 
End If

WsDir2Length = Len(WsDir2)

Dim StdIn, StdOut
Set StdIn = WScript.StdIn
Set StdOut = WScript.StdOut
Set StdErr = WScript.StdErr

Do While Not StdIn.AtEndOfStream
  str = StdIn.ReadLine
  FullPath = FileSystem.GetAbsolutePathName(str)
  If WsDir = "" Then
    StdOut.WriteLine FullPath
  Else
    If Instr(FullPath, WsDir2) <> 1 Then
      StdErr.WriteLine "ERROR: " & FullPath & " does not belong to " & WsDir
    Else
      StdOut.WriteLine Mid(FullPath, WsDir2Length + 1)
    End If
  End If
Loop
