# Metrics Monitor (Distributed `htop` for Docker Compose)

Et distribueret, letvægts monitoreringssystem til Linux-containere inspireret af værktøjer som `htop`, `btop` og Prometheus.

---

## 🎯 Projektets Formål & Idé
At bygge et centralt TUI-dashboard (Terminal User Interface) i **Go**, der modtager live system-metrics (CPU, RAM m.m.) i realtid over netværket fra flere uafhængige, ultrahurtige agenter skrevet i **C**, som kører i hver deres Docker-container via **Docker Compose**.

Ingen enterprise-bloat, ingen tunge frameworks – bare ren, effektiv kode tæt på styresystemet med øjeblikkelig visuel feedback i terminalen.

---

## 🏗️ Arkitektur & Teknologi-stak

```text
[ Container: Agent 1 (C) ]  ──(TCP / Binary / JSON)──┐
[ Container: Agent 2 (C) ]  ──(TCP / Binary / JSON)──┼──> [ Container: Central Hub / Server (Go) ]
[ Container: Agent 3 (C) ]  ──(TCP / Binary / JSON)──┘                  │
                                                                        ▼
                                                             [ Terminal TUI Dashboard ]
                                                             (Go + Charm.sh Bubbletea)
```

1. **Agent (C):**
   * Læser direkte fra Linux-kernen via `/proc/stat` og `/proc/meminfo`.
   * Høj performance, minimalt fodaftryk (< 50 KB binær, < 2 MB RAM).
   * Sender målinger periodisk via en rå TCP socket.

2. **Server & TUI Dashboard (Go):**
   * Modtager data fra vilkårligt mange samtidige agenter vha. `goroutines` og `channels`.
   * Holder seneste historik for hver forbundet node i hukommelsen.
   * Renders et flot og responsivt terminal-dashboard med [Bubbletea / Lipgloss](https://github.com/charmbracelet/bubbletea) med fuld tastatur-/Vim-navigation.

3. **Orkestrering (Docker Compose):**
   * Kører serveren og et vilkårligt antal agenter i et internt virtuelt netværk:
     ```bash
     docker compose up --scale agent=5
     ```

---

## 🚀 Køreplan / Faser

### Fase 1: Den lokale C-agent
* Læs CPU- og RAM-forbrug direkte fra `/proc/stat` og `/proc/meminfo`.
* Beregn CPU-procent over tid ($\Delta \text{work} / \Delta \text{total}$).
* Udskriv formaterede målinger til terminalen.

### Fase 2: Netværkslag (C ➔ Go)
* Opret en TCP-server i Go, der lytter på en defineret port.
* Opret socket-forbindelse fra C-agenten og send metrikker over netværket hvert sekund.
* Håndter gentilkobling og registrering af unikke node-ID'er / hostnames.

### Fase 3: Det visuelle TUI-dashboard (Go + Bubbletea)
* Byg dashboardet med Elm-arkitekturen (Model-Update-View).
* Vis gitter/liste over alle tilkoblede containere/noder med live CPU/RAM-barer (`[||||......] 42%`).
* Tilføj Vim-navigation (`j`/`k` / piletaster) til at vælge og inspicere en bestemt container.

### Fase 4: Docker Compose & Skalering
* Opret minimale Dockerfiles for henholdsvis C-agenten (Alpine/Scratch) og Go-serveren.
* Opsæt `docker-compose.yml` med virtuelt netværk.
* Test skalering med `--scale agent=X` og se nye noder poppe op i realtid.
