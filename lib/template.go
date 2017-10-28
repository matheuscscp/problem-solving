package main

// =============================================================================
// BEGIN template
// =============================================================================
import (
  "fmt"
  "bufio"
  "os"
)

// io
var stdin *bufio.Reader
var stdout *bufio.Writer
func fastio() {
  stdin = bufio.NewReader(os.Stdin)
  stdout = bufio.NewWriter(os.Stdout)
}
func scan(buf ...interface{}) {
  for _, a := range buf {
    fmt.Fscan(stdin, a)
  }
}
func dbg(x ...interface{}) {
  if os.Getenv("LOCAL") != "true" {
    return
  }
  fmt.Fprint(os.Stderr, ">>>>")
  for _, a := range x {
    fmt.Fprint(os.Stderr, " ", a)
  }
  fmt.Fprintln(os.Stderr)
}

// helpers
func min(x, y int64) int64 {
  if x < y {
    return x
  }
  return y
}
// =============================================================================
// END template
// =============================================================================

func main() {
  fastio()
  
  stdout.Flush()
}
