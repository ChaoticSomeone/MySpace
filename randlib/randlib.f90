module randlib
implicit none

integer :: prevSeed

contains

	function NewRand(RANDLIB_MAX)
		implicit none
		integer :: RANDLIB_MAX
		integer :: NewRand
		integer :: values(8)
		integer :: i, seed
	
		do while(seed == prevSeed)
			call date_and_time(values=values)
			seed = 1
			do i=1, 8
				if (values(i) == 0) then
					seed = seed + values(i)
				else
				seed = seed * values(i)
				end if
			end do
		end do
		prevSeed = seed
		NewRand = 8253739 * seed + 2396403
		NewRand = modulo(newRand, RANDLIB_MAX)
	end function NewRand

	function Randint(min, max, RANDLIB_MAX)
		implicit none
		integer :: r
		integer :: Randint
		integer :: min, max, RANDLIB_MAX
		r = NewRand(RANDLIB_MAX)
		Randint = min + modulo(r, max - min +1)
	end function Randint

	function Randfloat(min, max, RANDLIB_MAX)
		implicit none
		integer :: r
		integer :: min, max, RANDLIB_MAX
		real :: Randfloat
		real ::  pre, post

		pre = Randint(floor(REAL(min)), floor(REAL(max))-1, RANDLIB_MAX)
		post = NewRand(RANDLIB_MAX)
		post = post / 10**(floor(log10(REAL(RANDLIB_MAX))))
		Randfloat = pre + post
	end function Randfloat

	function Randbool()
		implicit none
		logical :: Randbool
		integer :: num
	
		num = modulo(NewRand(32767), 2)
		if (num == 1) then
			Randbool = .true.
		else
			Randbool = .false.
		end if
	end function Randbool

	function Randchar(excludeWhitespaces)
		character :: Randchar
		logical :: excludeWhitespaces
		integer :: ascii_code
		integer, dimension(3) :: whitespaces = (/9, 10, 32/)

		if (.not.(excludeWhitespaces) .and. Randint(0,6,32767) == 0) then
			ascii_code = whitespaces(Randint(1,3,32767))
		else
			ascii_code = Randint(33,126,32767)
		end if
		Randchar = achar(ascii_code)
	end function Randchar


end module randlib
