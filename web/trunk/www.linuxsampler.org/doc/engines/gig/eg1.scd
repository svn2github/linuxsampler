Storage 
{
	{ Format 1.33 }
	{ GeneratedFrom TSCD-version-2.20 }
	{ WrittenBy cuse }
	{ WrittenOn "" }
}

Document 
{
	{ Type "Statechart Diagram" }
	{ Name eg1.scd }
	{ Author cuse }
	{ CreatedOn "" }
	{ Annotation "" }
	{ Hierarchy True }
}

Page 
{
	{ PageOrientation Portrait }
	{ PageSize A4 }
	{ ShowHeaders False }
	{ ShowFooters False }
	{ ShowNumbers False }
}

Scale 
{
	{ ScaleValue 1 }
}

# GRAPH NODES

SCDOrState 1
{
	{ Name "Attack\r\rdo: raise level lin.\rdo: count time" }
	{ Annotation "" }
	{ Parent 0 }
	{ Index "" }
}

SCDOrState 2
{
	{ Name "Attack_Hold\r\rdo: hold level" }
	{ Annotation "" }
	{ Parent 0 }
	{ Index "" }
}

SCDOrState 3
{
	{ Name "Decay_1\r\rdo: reduce level exp.\rdo: count time" }
	{ Annotation "" }
	{ Parent 0 }
	{ Index "" }
}

SCDOrState 4
{
	{ Name "Decay_2\r\rdo: reduce level exp." }
	{ Annotation "" }
	{ Parent 0 }
	{ Index "" }
}

SCDOrState 5
{
	{ Name "Sustain\r\rdo: hold level" }
	{ Annotation "" }
	{ Parent 0 }
	{ Index "" }
}

SCDOrState 6
{
	{ Name "Release\r\rdo: reduce level exp." }
	{ Annotation "" }
	{ Parent 0 }
	{ Index "" }
}

SCDFinalState 7
{
	{ Name "" }
	{ Annotation "" }
	{ Parent 0 }
	{ Index "" }
}

SDCDefaultState 8
{
	{ Name "" }
	{ Annotation "" }
	{ Parent 0 }
	{ Index "" }
}

Comment 40
{
	{ Name "gig::Engine\rEnvelope Generator 1 (Amplitude / VCA EG)" }
	{ Annotation "" }
	{ Parent 0 }
	{ Index "" }
}

# GRAPH EDGES

SCDTransitionEdge 9
{
	{ Name "Voice triggered\r/ set level = PreAttack" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 8 }
	{ Subject2 1 }
}

SCDTransitionEdge 10
{
	{ Name "Attack time reached\r[AttackHold flag set]" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 1 }
	{ Subject2 2 }
}

SCDTransitionEdge 11
{
	{ Name "Attack time reached\r[AttackHold flag not set]" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 1 }
	{ Subject2 3 }
}

SCDTransitionEdge 12
{
	{ Name "Playback reached Loop start" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 2 }
	{ Subject2 3 }
}

SCDTransitionEdge 13
{
	{ Name "Decay_1 time reached\r[InfiniteSustain flag not set]" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 3 }
	{ Subject2 4 }
}

SCDTransitionEdge 14
{
	{ Name "Decay_1 time reached\r[InfiniteSustain flag set]" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 3 }
	{ Subject2 5 }
}

SCDTransitionEdge 15
{
	{ Name "Voice released" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 5 }
	{ Subject2 6 }
}

SCDTransitionEdge 16
{
	{ Name "Voice released" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 4 }
	{ Subject2 6 }
}

SCDTransitionEdge 17
{
	{ Name "level < min. level" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 6 }
	{ Subject2 7 }
}

SCDTransitionEdge 36
{
	{ Name "Release cancelled\r[InfiniteSustain flag set]" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 6 }
	{ Subject2 5 }
}

SCDTransitionEdge 37
{
	{ Name "Release cancelled\r[InfiniteSustain flag not set]" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 6 }
	{ Subject2 4 }
}

SCDTransitionEdge 42
{
	{ Name "level < min. level" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 4 }
	{ Subject2 7 }
}

SCDTransitionEdge 44
{
	{ Name "Voice released" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 2 }
	{ Subject2 6 }
}

SCDTransitionEdge 45
{
	{ Name "Voice released" }
	{ Annotation "" }
	{ Parent 0 }
	{ Subject1 3 }
	{ Subject2 6 }
}

# VIEWS AND GRAPHICAL SHAPES

View 18
{
	{ Index "0" }
	{ Parent 0 }
}

RoundedBox 19
{
	{ View 18 }
	{ Subject 1 }
	{ Position 230 190 }
	{ Size 172 60 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FillStyle Unfilled }
	{ FillColor "white" }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

RoundedBox 20
{
	{ View 18 }
	{ Subject 2 }
	{ Position 580 190 }
	{ Size 116 46 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FillStyle Unfilled }
	{ FillColor "white" }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

RoundedBox 21
{
	{ View 18 }
	{ Subject 3 }
	{ Position 230 330 }
	{ Size 180 68 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FillStyle Unfilled }
	{ FillColor "white" }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

RoundedBox 22
{
	{ View 18 }
	{ Subject 4 }
	{ Position 530 460 }
	{ Size 172 46 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FillStyle Unfilled }
	{ FillColor "white" }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

RoundedBox 23
{
	{ View 18 }
	{ Subject 5 }
	{ Position 90 460 }
	{ Size 116 46 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FillStyle Unfilled }
	{ FillColor "white" }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

RoundedBox 24
{
	{ View 18 }
	{ Subject 6 }
	{ Position 310 620 }
	{ Size 172 46 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FillStyle Unfilled }
	{ FillColor "white" }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

BullsEye 25
{
	{ View 18 }
	{ Subject 7 }
	{ Position 310 710 }
	{ Size 20 20 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FillStyle Unfilled }
	{ FillColor "white" }
	{ FixedName True }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

BlackDot 26
{
	{ View 18 }
	{ Subject 8 }
	{ Position 230 90 }
	{ Size 8 8 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FillStyle Unfilled }
	{ FillColor "white" }
	{ FixedName True }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 27
{
	{ View 18 }
	{ Subject 9 }
	{ FromShape 26 }
	{ ToShape 19 }
	{ Curved False }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 2 }
	{ Point 230 94 }
	{ Point 230 160 }
	{ NamePosition 220 125 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 28
{
	{ View 18 }
	{ Subject 10 }
	{ FromShape 19 }
	{ ToShape 20 }
	{ Curved False }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 2 }
	{ Point 316 190 }
	{ Point 522 190 }
	{ NamePosition 421 190 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 29
{
	{ View 18 }
	{ Subject 11 }
	{ FromShape 19 }
	{ ToShape 21 }
	{ Curved False }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 2 }
	{ Point 230 220 }
	{ Point 230 296 }
	{ NamePosition 216 258 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 30
{
	{ View 18 }
	{ Subject 12 }
	{ FromShape 20 }
	{ ToShape 21 }
	{ Curved True }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 4 }
	{ Point 550 213 }
	{ Point 550 280 }
	{ Point 460 300 }
	{ Point 320 318 }
	{ NamePosition 489 286 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 31
{
	{ View 18 }
	{ Subject 13 }
	{ FromShape 21 }
	{ ToShape 22 }
	{ Curved True }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 4 }
	{ Point 320 340 }
	{ Point 450 340 }
	{ Point 520 380 }
	{ Point 520 437 }
	{ NamePosition 476 368 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 32
{
	{ View 18 }
	{ Subject 14 }
	{ FromShape 21 }
	{ ToShape 23 }
	{ Curved True }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 4 }
	{ Point 140 340 }
	{ Point 100 340 }
	{ Point 70 390 }
	{ Point 70 437 }
	{ NamePosition 105 386 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 33
{
	{ View 18 }
	{ Subject 15 }
	{ FromShape 23 }
	{ ToShape 24 }
	{ Curved True }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 4 }
	{ Point 60 483 }
	{ Point 60 560 }
	{ Point 120 630 }
	{ Point 224 630 }
	{ NamePosition 101 581 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 34
{
	{ View 18 }
	{ Subject 16 }
	{ FromShape 22 }
	{ ToShape 24 }
	{ Curved True }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 4 }
	{ Point 542 483 }
	{ Point 540 550 }
	{ Point 480 610 }
	{ Point 396 610 }
	{ NamePosition 486 577 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 35
{
	{ View 18 }
	{ Subject 17 }
	{ FromShape 24 }
	{ ToShape 25 }
	{ Curved False }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 2 }
	{ Point 310 643 }
	{ Point 310 700 }
	{ NamePosition 334 674 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 38
{
	{ View 18 }
	{ Subject 36 }
	{ FromShape 24 }
	{ ToShape 23 }
	{ Curved True }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 4 }
	{ Point 270 597 }
	{ Point 270 550 }
	{ Point 220 470 }
	{ Point 148 470 }
	{ NamePosition 195 507 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 39
{
	{ View 18 }
	{ Subject 37 }
	{ FromShape 24 }
	{ ToShape 22 }
	{ Curved True }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 4 }
	{ Point 360 597 }
	{ Point 360 540 }
	{ Point 390 480 }
	{ Point 444 472 }
	{ NamePosition 399 536 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

TextBox 41
{
	{ View 18 }
	{ Subject 40 }
	{ Position 180 40 }
	{ Size 20 20 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FillStyle Unfilled }
	{ FillColor "white" }
	{ FixedName False }
	{ Font "-*-courier-bold-r-normal--10*" }
	{ TextAlignment Left }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 43
{
	{ View 18 }
	{ Subject 42 }
	{ FromShape 22 }
	{ ToShape 25 }
	{ Curved True }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 4 }
	{ Point 580 483 }
	{ Point 580 630 }
	{ Point 430 700 }
	{ Point 320 709 }
	{ NamePosition 484 643 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 46
{
	{ View 18 }
	{ Subject 44 }
	{ FromShape 20 }
	{ ToShape 24 }
	{ Curved True }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 4 }
	{ Point 615 213 }
	{ Point 720 870 }
	{ Point 190 820 }
	{ Point 264 643 }
	{ NamePosition 474 732 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

Line 47
{
	{ View 18 }
	{ Subject 45 }
	{ FromShape 21 }
	{ ToShape 24 }
	{ Curved True }
	{ End1 Empty }
	{ End2 FilledArrow }
	{ Points 4 }
	{ Point 241 364 }
	{ Point 290 410 }
	{ Point 310 480 }
	{ Point 310 597 }
	{ NamePosition 300 445 }
	{ Color "black" }
	{ LineWidth 1 }
	{ LineStyle Solid }
	{ FixedName False }
	{ Font "-*-courier-medium-r-normal--10*" }
	{ TextAlignment Center }
	{ TextColor "black" }
	{ NameUnderlined False }
}

