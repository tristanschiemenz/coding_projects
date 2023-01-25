package main

import (
	"booking-app/helper"
	"fmt"
	"strconv"
	"strings"
	"sync"
	"time"
)

var goferenceName string = "Go Conferences"
var remaingTickets uint = 50

var wg = sync.WaitGroup{}

func main() {

	greed_users(goferenceName, remaingTickets)

	//GO Datatyp: string, integer, booleans, maps, arrays

	var bookings []string

	for remaingTickets > 0 && len(bookings) < 50 {
		var firstName string
		var lastName string
		var userEmail string
		var ticketNumber uint

		//ask user for name
		fmt.Println("Enter your Firstname:")
		fmt.Scan(&firstName)

		fmt.Println("Enter your Lastname:")
		fmt.Scan(&lastName)

		fmt.Println("Enter your Email:")
		fmt.Scan(&userEmail)

		fmt.Println("Enter Number of Tickets:")
		fmt.Scan(&ticketNumber)
		wg.Add(1)
		go test()

		isValidName, isValidEmail, isValidTickets := helper.ValidateUser(firstName, lastName, userEmail, ticketNumber, remaingTickets)

		if isValidName && isValidEmail && isValidTickets {
			//create a map for the userdata
			var userdata = make(map[string]string)

			userdata["firstName"] = firstName
			userdata["lastName"] = lastName
			userdata["userEmail"] = userEmail
			userdata["ticketNumber"] = strconv.FormatUint(uint64(ticketNumber), 10)

			remaingTickets = remaingTickets - uint(ticketNumber)

			bookings = append(bookings, firstName+" "+lastName)

			fmt.Printf("Thank you!!!\nName: %v %v\nEMail: %v\nTickets booked: %v\n", firstName, lastName, userEmail, ticketNumber)

			fmt.Printf("%v tickets remaing for %v\n", remaingTickets, goferenceName)

			firstNames := get_firstnames(bookings)
			fmt.Println(firstNames)

		} else {
			fmt.Printf("Informations validation check:\nName: %v\nEmail: %v\nTicketnumber: %v\n", isValidName, isValidEmail, isValidTickets)
		}
		wg.Wait()
	}
}
func greed_users(goferenceName string, conferenceTickets uint) {
	fmt.Printf("Welcome to my the %v booking application\n", goferenceName)
	fmt.Printf("Total Tickets: %v \n", conferenceTickets)
}
func get_firstnames(bookings []string) []string {
	var firstNamesslice []string
	for _, booking := range bookings {
		var names = strings.Fields(booking)
		firstNamesslice = append(firstNamesslice, names[0])
	}
	return firstNamesslice
}

type userData struct {
	firstName       string
	lastName        string
	Email           string
	numberOfTickets uint
}

func test() {
	time.Sleep(10 * time.Second)
	fmt.Println("Ten seconds are thought")
	wg.Done()
}
