p1 <- function(x) {
  +3.89817e-17*(x - 0)+0
}
p2 <- function(x) {
  +0.0450316*(x - 0)*(x - 4.71239)-0.212207*(x - 0)+0
}
p3 <- function(x) {
  +7.89935e-18*(x - 0)*(x - 3.14159)*(x - 6.28319)-2.48165e-17*(x - 0)*(x - 3.14159)+3.89817e-17*(x - 0)+0
}
p4 <- function(x) {
  -0.0157589*(x - 0)*(x - 2.35619)*(x - 4.71239)*(x - 7.06858)+0.074262*(x - 0)*(x - 2.35619)*(x - 4.71239)-0.217432*(x - 0)*(x - 2.35619)+0.300105*(x - 0)+0
}
p5 <- function(x) {
  -1.86623e-18*(x - 0)*(x - 1.88496)*(x - 3.76991)*(x - 5.65487)*(x - 7.53982)-0.013297*(x - 0)*(x - 1.88496)*(x - 3.76991)*(x - 5.65487)+0.100257*(x - 0)*(x - 1.88496)*(x - 3.76991)-0.350388*(x - 0)*(x - 1.88496)+0.504551*(x - 0)+0
}


pdf("p1.pdf")
plot(function(x) { abs(sin(x) - p1(x)) }, from=0, to=3*pi, ylim=c(-3, 3), main="Erreur avec polynôme ordre 1")
dev.off()

pdf("p2.pdf")
plot(function(x) { abs(sin(x) - p2(x)) }, from=0, to=3*pi, ylim=c(-3, 3), main="Erreur avec polynôme ordre 2")
dev.off()

pdf("p3.pdf")
plot(function(x) { abs(sin(x) - p3(x)) }, from=0, to=3*pi, ylim=c(-3, 3), main="Erreur avec polynôme ordre 3")
dev.off()

pdf("p4.pdf")
plot(function(x) { abs(sin(x) - p4(x)) }, from=0, to=3*pi, ylim=c(-3, 3), main="Erreur avec polynôme ordre 4")
dev.off()

pdf("p5.pdf")
plot(function(x) { abs(sin(x) - p5(x)) }, from=0, to=3*pi, ylim=c(-3, 3), main="Erreur avec polynôme ordre 5")
dev.off()
