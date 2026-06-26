# Break Projects

Break projects are hands-on chapters built around a specific electronic device you purchased. They are not pre-planned — the agenda holds placeholder slots (BP-01 through BP-05), and the content is created on-demand when you bring a device.

## When to Start a Break Project

After completing a full tier (Foundations, Entry, Novice, Intermediate, Expert). Break projects apply the skills from the just-completed tier to a real device.

## How It Works

1. **You provide the device** — bring it to a session with any markings, labels, or packaging info
2. **Identify the driver IC** — decode the module markings using F08 skills
3. **Find the datasheet** — locate the device datasheet using F09 skills; we read the interface and init sequence together
4. **Wire it up** — use the NUCLEO-L476RG schematic (UM1724) to choose the right pins; check voltage levels (3.3V logic)
5. **Write the driver** — bare metal driver from scratch using the communication peripheral skills from completed tiers (no vendor libs for the device)
6. **Build a demo** — a small working application that uses the device meaningfully
7. **Document it** — add a `README.md` to the project folder

## Project Folder Structure

Each break project lives at:
```
break-projects/
└── bpNN-device-name/
    ├── CMakeLists.txt
    ├── README.md               ← device description, wiring diagram (ASCII or photo link), what you learned
    ├── src/
    │   ├── main.c
    │   └── <device_name>.c     ← the bare metal driver
    └── inc/
        └── <device_name>.h
```

## Completed Break Projects

| Slot | Device | Interface | Date | Notes |
|------|--------|-----------|------|-------|
| BP-01 | TBD | TBD | — | After Foundations tier |
| BP-02 | TBD | TBD | — | After Entry tier |
| BP-03 | TBD | TBD | — | After Novice tier |
| BP-04 | TBD | TBD | — | After Intermediate tier |
| BP-05 | TBD | TBD | — | After Expert tier |
