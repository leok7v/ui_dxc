# ui_dxc

experiments with DirectDraw DirectWrite GDI interop in C

[![build-on-push](https://github.com/leok7v/ui_dxc/actions/workflows/build-on-push.yml/badge.svg)](https://github.com/leok7v/ui_dxc/actions/workflows/build-on-push.yml)

![HelloWorld](https://github.com/leok7v/ui_dxc/assets/1149445/facc4db2-339f-4524-bf6e-f2f3542da0dd)

MacBook Air M3 2024, Windows 11, Parallels, main 4K monitor 3870x2516:

* CreateSolidColorBrush: 123ns (nanoseconds)
* CreateSolidColorBrush.SetColor): 36ns (nanoseconds)
* CreateTextFormat: 607ns (nanoseconds)
* CreateTextFormat.CreateTextLayout.GetMetrics(): 23us (microseconds)
* CreateTextFormat.SetWordWrapping(): 32ns (nanoseconds)
* CreateTextFormat.DrawText(): 360us (microseconds)

![GDIvsDirectDraw](https://github.com/leok7v/ui_dxc/assets/1149445/1622eb17-afc1-4342-803f-9ee287e2386f)

MacBook Pro 9,1 June 2012 i7-3615QM, Windows 10 BootCamp, 2K Monitor 2560x1440 

* CreateSolidColorBrush: 356ns (nanoseconds)
* CreateSolidColorBrush.SetColor): 22ns (nanoseconds)
* CreateTextFormat: 1770ns (nanoseconds)
* CreateTextFormat.CreateTextLayout.GetMetrics(): 68us (microseconds)
* CreateTextFormat.SetWordWrapping(): 3ns (nanoseconds)
* CreateTextFormat.DrawText(): 91us (microseconds)

DWrite vs GDI PROOF_QUALITY 12px high 9pt font:

![DWrite_vs_GDI__PROOF_QUALITY](https://github.com/leok7v/ui_dxc/assets/1149445/95b64cc5-9eff-4c10-ba14-e5a6940585ac)

DWrite vs GDI ANTIALIASED_QUALITY 12px high 9pt font:

![DWrite_vs_GDI_ANTIALIASED_QUALITY](https://github.com/leok7v/ui_dxc/assets/1149445/f5a5d46d-5787-4347-99b7-192dc4580d7d)

