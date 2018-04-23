// github.com/mlowicki/barrier2
//The code for the barrier was taken from this website: https://medium.com/golangspec/reusable-barriers-in-golang-156db1f75d0b

package barrier

import "sync"


type Barrier struct {
    c      int
    n      int
    m      sync.Mutex
    before chan int
    after  chan int
}
func New(n int) *Barrier {
    b := Barrier{
        n:      n,
        before: make(chan int, n),
        after:  make(chan int, n),
    }
    return &b
}
func (b *Barrier) Before() {
    b.m.Lock()
    b.c += 1
    if b.c == b.n {
        // open 2nd gate
        for i := 0; i < b.n; i++ {
            b.before <- 1
        }
    }
    b.m.Unlock()
    <-b.before
}
func (b *Barrier) After() {
    b.m.Lock()
    b.c -= 1
    if b.c == 0 {
        // open 1st gate
        for i := 0; i < b.n; i++ {
            b.after <- 1
        }
    }
    b.m.Unlock()
    <-b.after
}
