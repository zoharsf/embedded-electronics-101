# MkDocs Documentation

This directory contains the MkDocs documentation for the Embedded Electronics 101 workshop series.

## 🌐 Published Site

Once deployed, this site will be published at:
`https://zoharsf.github.io/embedded-electronics-101/`

## 📁 Structure

```
docs/
├── index.md              # Home page
├── pre-workshop.md       # Pre-workshop homework guide
├── workshop-1.md         # Workshop 1 guide
├── inter-workshop.md     # Inter-workshop homework
├── workshop-2.md         # Workshop 2 guide
├── inter-workshop-2.md   # Inter-workshop 2 homework
├── workshop-3.md         # Workshop 3 guide
├── resources.md          # Resources and project ideas
└── README.md             # This file

mkdocs.yml                # MkDocs configuration (in root)
requirements.txt          # Python dependencies (in root)
```

## ⚙️ Setup Instructions

### Prerequisites

- Python 3.8 or higher
- uv (fast Python package installer)

### Installation

1. **Install uv** (if not already installed):
   ```bash
   curl -LsSf https://astral.sh/uv/install.sh | sh
   ```

2. **Install dependencies**:
   ```bash
   uv sync
   ```

3. **Serve locally** (for testing):
   ```bash
   uv run mkdocs serve
   ```
   
   Open http://127.0.0.1:8000 in your browser

3. **Build the site**:
   ```bash
   uv run mkdocs build
   ```
   
   This creates a `site/` directory with static HTML files

## 🚀 GitHub Pages Deployment

MkDocs can deploy to GitHub Pages automatically:

### Method 1: GitHub Actions (Recommended)

A GitHub Actions workflow has been created that automatically builds and deploys on every push to `main`.

Just push your changes - the site updates automatically!

### Method 2: Manual Deployment

```bash
uv run mkdocs gh-deploy
```

This command:
- Builds your site
- Creates/updates the `gh-pages` branch
- Pushes to GitHub
- GitHub Pages serves from `gh-pages` branch

### GitHub Pages Configuration

1. Go to repository Settings → Pages
2. Source: "Deploy from a branch"
3. Branch: `gh-pages` (created automatically)
4. Folder: `/ (root)`
5. Save

## 🎨 Theme

This site uses the **Material for MkDocs** theme, which provides:
- Modern, responsive design
- Dark/light mode toggle
- Built-in search
- Syntax highlighting
- Navigation tabs
- Code copy buttons
- Mermaid diagram support
- Mobile-friendly layout

## 🔧 Local Development

### Serve with live reload:
```bash
uv run mkdocs serve
```

Changes to markdown files are reflected immediately!

### Build for production:
```bash
uv run mkdocs build --strict
```

The `--strict` flag treats warnings as errors.

### Clean build:
```bash
uv run mkdocs build --clean
```

## 📝 Editing Content

All content is written in Markdown (`.md` files). To edit:

1. Open any `.md` file in the `docs/` directory
2. Edit using standard Markdown syntax
3. Save and view changes in browser (if using `mkdocs serve`)
4. Commit and push - GitHub Actions deploys automatically

### Navigation

Edit the `nav` section in `mkdocs.yml` to change site navigation:

```yaml
nav:
  - Home: index.md
  - Workshop 1: workshop-1.md
  # etc.
```

## 🔗 Internal Links

MkDocs uses `.md` extension for internal links:
- `[Workshop 1](workshop-1.md)`
- `[Resources](resources.md)`

External links use full URLs:
- `[GitHub Repo](https://github.com/zoharsf/embedded-electronics-101)`

## 📊 Features

### Code Highlighting

Supports syntax highlighting for Arduino, Python, and more:

\`\`\`cpp
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
}
\`\`\`

### Mermaid Diagrams

Create flowcharts and diagrams:

\`\`\`mermaid
graph LR
    A[Start] --> B[Workshop 1]
    B --> C[Workshop 2]
\`\`\`

### Admonitions

Create note boxes:

```markdown
!!! note "Important"
    This is a note box
```

### Tables

Standard markdown tables work:

```markdown
| Component | Quantity |
|-----------|----------|
| ESP32     | 1        |
| LED       | 3        |
```

## 🎨 Customization

### Change Theme Colors

Edit `mkdocs.yml`:

```yaml
theme:
  palette:
    primary: indigo  # Change to: red, pink, purple, deep-purple, indigo, blue, etc.
    accent: purple
```

### Add Custom CSS

1. Create `docs/stylesheets/extra.css`
2. Add to `mkdocs.yml`:
   ```yaml
   extra_css:
     - stylesheets/extra.css
   ```

### Add Custom JavaScript

1. Create `docs/javascripts/extra.js`
2. Add to `mkdocs.yml`:
   ```yaml
   extra_javascript:
     - javascripts/extra.js
   ```

## 🆘 Troubleshooting

### Site not building?
- Check for syntax errors in markdown files
- Verify `mkdocs.yml` is valid YAML
- Run `uv run mkdocs build --strict` to see detailed errors

### Changes not showing?
- Clear browser cache (Cmd+Shift+R / Ctrl+F5)
- Wait for GitHub Actions to complete (~1-2 minutes)
- Check Actions tab for deployment status

### Links broken?
- Use relative paths: `workshop-1.md` not `workshop-1.html`
- Ensure linked files exist in `docs/` directory
- Check for typos in filenames

### Theme not loading?
- Verify `mkdocs-material` is installed: `uv pip list | grep mkdocs-material`
- Check `pyproject.toml` is up to date
- Run `uv sync` again

## 📚 More Information

- [MkDocs Documentation](https://www.mkdocs.org/)
- [Material for MkDocs](https://squidfunk.github.io/mkdocs-material/)
- [Markdown Guide](https://www.markdownguide.org/)
- [GitHub Pages with MkDocs](https://www.mkdocs.org/user-guide/deploying-your-docs/)

## 🔄 Updating Dependencies

To update MkDocs and plugins:

```bash
uv sync --upgrade
```

## ✅ Pre-Deployment Checklist

- [ ] All markdown files have no syntax errors
- [ ] Internal links work (use `.md` extension)
- [ ] Code blocks have proper syntax highlighting
- [ ] Site builds without warnings: `mkdocs build --strict`
- [ ] Local preview looks good: `mkdocs serve`
- [ ] Navigation structure is correct in `mkdocs.yml`
- [ ] GitHub Actions workflow exists
- [ ] GitHub Pages enabled in repository settings
