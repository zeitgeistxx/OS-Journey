package main

import (
	"fmt"
	"io"
	"net/http"
)

func main() {
	res, err := http.Get("https://github.com/kanisterio/kanister/releases/download/0.80.0/checksums.txt")

	if err != nil {
		fmt.Println(err.Error())
		return
	}

	data, err := io.ReadAll(res.Body)

	if err != nil {
		fmt.Println(err.Error())
		return
	}

	fmt.Printf("%s", data)
}
