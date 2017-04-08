package main
import "fmt"

func main () {
    var n int
    fmt.Scan(&n)

    v := make([]int, n)
    for i := 0; i < n; i++ {
        fmt.Scan(&v[i])
    }

    var c int = 'a'

    var q int = 0

    for i := 0; i < n; i++ {
        if v[q] > 0 {
            for j := 0; j <= q; j++ {
                v[q]--
            }
            q++
            fmt.Printf("%c", c)
        } else {
            q = 0
            c++
            if (c == 'z') {
                c = 'a'
            }
            i--
        }
    }
    fmt.Printf("\n")
}
