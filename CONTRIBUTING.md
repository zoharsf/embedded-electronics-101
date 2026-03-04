# Contributing to Embedded Electronics 101

Thanks for your interest in improving this workshop series! Here's how you can help.

## Reporting Issues

- **Broken links:** Open an issue with the file path and the broken URL
- **Incorrect information:** Describe what's wrong and what the correct information should be
- **Typos or unclear instructions:** Point us to the specific section

## Suggesting Improvements

- **New project ideas:** Open an issue describing the project and which workshop level it fits
- **Better explanations:** If something was confusing when you went through the workshop, let us know
- **Additional resources:** Suggest useful links, videos, or tools

## Making Changes

### Setup

1. Fork the repository
2. Clone your fork
3. Install dependencies for the docs site:
   ```bash
   pip install uv
   uv sync
   ```
4. Preview the docs site locally:
   ```bash
   mkdocs serve
   ```
   Then visit `http://localhost:8000`

### Code Style

**Arduino sketches (.ino files):**
- Include a header comment block with project name, hardware needed, pin connections, and required libraries
- Use `const int` for pin definitions
- Comment generously — these are educational examples
- Include a "Try This" section at the bottom with experiment suggestions

**Markdown files:**
- Use relative links (e.g., `./file.md` or `../folder/file.md`), not absolute paths
- Include learning objectives at the top of lesson files
- Add prev/next navigation at the bottom of lesson files
- Keep the tone beginner-friendly

### Pull Requests

1. Create a branch for your changes
2. Make your edits
3. Test the docs site locally with `mkdocs serve`
4. Submit a PR with a clear description of what you changed and why

## License

By contributing, you agree that your contributions will be licensed under the MIT License.
