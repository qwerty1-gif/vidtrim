# vidtrim

Requires ffmpeg to be installed.
Trims the first and last 5 seconds of a video using ffprobe and fftrim in C

Creates trimmed files named with "trim original"

Using Powershell with the command "get-childitem *.mp4 | foreach { rename-item $_ $_.Name.Replace("trim ", "") }", you can rename all the trim files to the originals(note that the original have to be removed before running the command).
