# Code Library for the Y-Badge
This code should be included as a subtree in the main project repository. Place it in the `src` directory of the main project repository.

Before working with this repository as a subtree, you should add a remote to your main project repository. This will allow you to pull and push changes to the subtree.

```bash
git remote add lib-y-badge git@github.com:y-badge/lib-y-badge.git
```

## To add the subtree
```bash
git subtree add --prefix src/lib-y-badge lib-y-badge main
```

## To update the subtree
```bash
git subtree pull --prefix src/lib-y-badge lib-y-badge main
```

## To push changes to the subtree
```bash
git subtree push --prefix src/lib-y-badge lib-y-badge main
```