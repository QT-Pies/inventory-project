# Contributing Guidelines

## Style Guide
Ideally, this will be a fairly short guide with just a few things we should all agree on for consistency purposes.

1. Spaces over tabs -- set your editor to do 4 spaces when you tab.
2. Classes should be PascalCased.
3. Functions should be camelCased.
4. Variables should be snake_cased.
5. Constants should be UPPER_SNAKE_CASED.
6. Function parameters should be constant when possible.
7. Function paremeters should be references when possible.
8. No using namespace std; use the std:: prefix to access members.
9. Favor the 'auto' keyword for long type names, such as iterators.
10. Curly braces should go on a newline.
11. Comments should not be redundant, but you should comment things that are unclear.
12. Favor use of smart pointers such as shared_ptr and unique_ptr rather than traditional C-style pointers.
13. C++ header files should end in the extension .hpp, and C++ source files should end in .cpp.

## Git Contributing
Rather than writing your changes on the main branch, please create a branch for the issue / feature you are working on.

We're likely going to use the GitHub issues page for tracking our work items; you can create your branch from here.

When you think you're finished with your work, open up a pull request to merge your branch with the main branch.  Post in the Discord that you need reviewers for a PR.  We're also going to look into setting up a CI build that needs to run before your PR can be merged.

Before you complete a PR, it should be approved by two reviewers and have passed the CI build.

### Git Step-by-Step - CLI instructions.
1. Create a new branch from the issue page for the issue you are working on.
2. Change directory to your local repo.
3. git fetch origin -- this will tell your local repo about the changes that have been made, i.e, the new branch.
4. git checkout branch-name -- this will change the branch you are currently working on.
5. git branch -- this will show you the branch you are actively working on, highlighted for you.  Use this to confirm you're on the correct branch.
6. git commit -- commit your changes to your branch.  Commit often.  Include issue # in commit message.
7. git push -- this will push your changes to the remote branch.  Do this often to avoid potential loss of commits.
8. When you think you're finished, open up a PR.

Ask in the Discord chat if you need any help with this process.
