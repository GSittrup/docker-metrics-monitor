# Metrics Monitor (Distributed `htop` for Docker Compose)

Et distribueret, letvægts monitoreringssystem til Linux-containere inspireret af værktøjer som `htop`, `btop` og Prometheus.


```text
[ Container: Agent 1 (C) ]  ──(TCP / Binary / JSON)──┐
[ Container: Agent 2 (C) ]  ──(TCP / Binary / JSON)──┼──> [ Container: Central Hub / Server (Go) ]
[ Container: Agent 3 (C) ]  ──(TCP / Binary / JSON)──┘                  │
                                                                        ▼
                                                             [ Terminal TUI Dashboard ]
                                                             (Go + Charm.sh Bubbletea)
```


### C-agent
* Læs CPU- og RAM-forbrug direkte fra `/proc/stat` og `/proc/meminfo`.
* Beregn CPU-procent over tid ($\Delta \text{work} / \Delta \text{total}$).
* Udskriv formaterede målinger til terminalen.

### Netværkslag (C ➔ Go)
* Opret en TCP-server i Go, der lytter på en defineret port.
* Opret socket-forbindelse fra C-agenten og send metrikker over netværket hvert sekund.
* Håndter gentilkobling og registrering af unikke node-ID'er / hostnames.

### TUI-dashboard (Go + Bubbletea)
* Byg dashboardet med Elm-arkitekturen (Model-Update-View).
* Vis gitter/liste over alle tilkoblede containere/noder med live CPU/RAM-barer (`[||||......] 42%`).
* Tilføj Vim-navigation (`j`/`k` / piletaster) til at vælge og inspicere en bestemt container.

### Docker Compose
* Opret minimale Dockerfiles for henholdsvis C-agenten (Alpine/Scratch) og Go-serveren.
* Opsæt `docker-compose.yml` med virtuelt netværk.
* Test skalering med `--scale agent=X` og se nye noder poppe op i realtid.
