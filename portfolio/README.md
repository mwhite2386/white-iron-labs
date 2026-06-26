# Portfolio — STM32 Training Showcase

## Purpose

A web portfolio to document and display the STM32 bare metal training journey completed in this workspace. Not built yet — planned for after the curriculum is substantially complete (months away).

## What It Will Show

- Chapter progress tracker (sourced from `curriculum/agenda.md`)
- Completed project code (linked to chapter folders under `boards/NUCLEO-L476RG/projects/`)
- Break project gallery: each device with wiring photos, demo videos, and driver code
- Skill progression from Foundations through Expert tier

## Data Sources (for Claude context)

| Content | Source |
|---------|--------|
| Chapter list and progress | `curriculum/agenda.md` — progress tracking table at bottom |
| Completed chapter code | `boards/NUCLEO-L476RG/projects/<tier>/chNN-*/` |
| Break project devices | `boards/NUCLEO-L476RG/projects/break-projects/bpNN-*/README.md` |
| Question log / learning journey | `curriculum/question-log.md` |

## Planned Features

- Chapter checklist with completion dates
- Embedded demo videos or GIFs per project
- Device gallery for break projects
- GitHub links to each project folder
- Skill tags per chapter (GPIO, DMA, I2C, etc.)

## Tech Stack

Not decided yet. When ready to build, choose based on:
- Static site (fast, cheap): Astro, Hugo, or plain HTML/CSS
- Interactive tracker: React or SvelteKit
- Hosting: GitHub Pages, Netlify, or Vercel

## Note for Claude

When the user asks to start building this portfolio, read `curriculum/agenda.md` first to understand the current completion state, then read a few completed chapter `README.md` files to understand the content style before proposing a site structure.
