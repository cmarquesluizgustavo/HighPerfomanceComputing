program main
    implicit none
    
    integer N
    real*8, dimension(:),   allocatable :: vector, result, resultJI
    real*8, dimension(:,:), allocatable :: matrix
    real start, finish, time_taken
    call random_seed()
    
    open(1, file = './results/fortran_IJ.csv', action = 'write')
    open(2, file = './results/fortran_JI.csv', action = 'write')
    
    do N = 1000, 33000, 1000

        allocate(vector(N))
        allocate(matrix(N, N))
    
        call randomVector(vector, N)
        call randomSquareMatrix(matrix, N)
    
        allocate(result(N))
        call emptyVector(result, N)
    
        call cpu_time(start)
        call matrixVectorMultiplyij(matrix, vector, result, N)
        call cpu_time(finish)
    
        time_taken =  finish - start
        print *, 'For size ', N, 'the matrix multiplication IJ took ', time_taken, ' second(s) to execute'
        write(1,*) N,",",time_taken
        deallocate(result)
    
        allocate(resultJI(N))
        call emptyVector(resultJI,N)
    
        call cpu_time(start )
        call matrixVectorMultiplyji(matrix,vector,resultJI,N)
        call cpu_time(finish )
    
        time_taken  =  finish  - start
        print *, 'For size ', N, 'the matrix multiplication JI took ', time_taken, ' second(s) to execute'
        write(2,*) N,",",time_taken
        deallocate(resultJI)
    
        deallocate(matrix)
        deallocate(vector)
    end do
    
    close(1)
    close(2)
    
    contains
    
    subroutine randomVector(vector, N)
        implicit none

        real(8), dimension(:) :: vector
        integer :: N, i
        real(8) :: number
        do i = 1, N
            call random_number(number)
            vector(i) = number * (N + 1)
        end do 
    end
    
    subroutine emptyVector(vector, N)
        implicit none

        real(8), dimension(:) :: vector
        integer :: N, i
        do i = 1, N
            vector(i) = 0
        end do 
    end
    
    subroutine randomSquareMatrix(matrix, N)
        implicit none

        real(8), dimension(:,:) :: matrix
        integer :: N, i, j
        real(8) :: number

        do i = 1, N
            do j = 1, N
                call random_number(number)
                matrix(i, j) = number * (N + 1)
            end do
        end do 
    end
    
    subroutine matrixVectorMultiplyij(matrix, vector, result, N)
        implicit none
    
        real*8, dimension(:,:) :: matrix
        real*8, dimension(:) :: vector, result
        integer :: N, i, j
    
        do i = 1, N
            do j = 1, N
                result(i) = result(i) + (matrix(i, j) * vector(j))
            end do
        end do
    end
    
    subroutine matrixVectorMultiplyji(matrix, vector, result, N)
        implicit none
    
        real*8, dimension(:,:) :: matrix
        real*8, dimension(:) :: vector, result
        integer :: N, i, j
    
        do j = 1, N
            do i = 1, N
                result(i) = result(i) + (matrix(i, j) * vector(j))
            end do
        end do
    end
    
    end program main
