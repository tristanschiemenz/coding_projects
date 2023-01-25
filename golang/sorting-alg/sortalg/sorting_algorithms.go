package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	var list []int
	max := 10000000
	x1 := rand.NewSource(time.Now().UnixNano())
	y1 := rand.New(x1)
	for i := 0; i < 1000; i++ {
		list = append(list, y1.Intn(max))
	}
	//sort the list with alg
	fmt.Println("Startung sortierung!")
	fmt.Println(Counting_sort(list))
	go Merge_sort(list)
	go Bubble_sort(list)
	go Selection_sort(list)
	go Insert_sort(list)

	time.Sleep(2000000 * time.Second)
}

// bubble sort
// time complexxity: worst case: n^2
func Bubble_sort(slice []int) []int {
	var n int = len(slice)
	var swapped bool = false

	for i := 0; i < n; i++ {
		for j := 0; j < n-i-1; j++ {
			if slice[j] > slice[j+1] {
				slice[j], slice[j+1] = slice[j+1], slice[j]
				swapped = true
			}
		}
		if !swapped {
			break
		}
	}
	fmt.Println("Bubble")
	return slice
}

// selection sort
// time complexxity: worst case: n^2
func Selection_sort(slice []int) []int {
	var n int = len(slice)
	for i := 0; i < n; i++ {
		min_index := i
		for j := i + 1; j < n; j++ {
			if slice[min_index] > slice[j] {
				min_index = j
			}
		}
		slice[i], slice[min_index] = slice[min_index], slice[i]
	}
	fmt.Println("Selection")
	return slice
}

// insert sort
// time complexxity: worst case: n^2
func Insert_sort(slice []int) []int {
	var n int = len(slice)
	for i := 1; i < n; i++ {
		key := slice[i]

		j := i - 1
		for j >= 0 && key < slice[j] {
			slice[j+1] = slice[j]
			j--
		}
		slice[j+1] = key
	}
	fmt.Println("Insert")
	return slice
}

// merge sort
// time complexxity: worts case: n*log(n)
func Merge_sort_function(slice []int) []int {

	if len(slice) < 2 {
		return slice
	}
	mid := (len(slice)) / 2

	return merge(Merge_sort_function(slice[:mid]), Merge_sort_function(slice[mid:]))
}
func merge(left []int, right []int) []int {
	size, i, j := len(left)+len(right), 0, 0

	slice := make([]int, size)

	for k := 0; k < size; k++ {
		if i > len(left)-1 && j <= len(right)-1 {
			slice[k] = right[j]
			j++

		} else if j > len(right)-1 && i <= len(left)-1 {
			slice[k] = left[i]
			i++

		} else if left[i] < right[j] {
			slice[k] = left[i]
			i++

		} else {
			slice[k] = right[j]
			j++
		}
	}
	return slice
}
func Merge_sort(slice []int) []int {
	slice = Merge_sort_function(slice)
	fmt.Println("Merge Sort")
	return slice
}

// counting sort
// time complexxity: worst case: n
func Counting_sort(slice []int) []int {
	var n int = len(slice)
	var max int
	for i := 1; i < n; i++ {

		if max < slice[i] {

			max = slice[i]
		}
	}

	var counter = make([]int, max)
	for i := 0; i < n; i++ {
		counter_postion := slice[i]
		counter[counter_postion] += 1
	}
	var k int = 0
	for i := 0; i < n; i++ {
		if counter[k] != 0 {
			slice[i] = k
			counter[k]--
		} else {
			k++
			slice[i] = k
			counter[k]--
		}
	}
	return slice
}
