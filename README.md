Shark
===============

A GUI typesetting display engine and cross platform GUI application development framework based on NodeJS/OpenGL

Goal: developing GUI applications on this basis can take into account both the simplicity and speed of developing WEB applications, as well as the performance and experience of Native applications.

一个GUI的排版显示引擎和跨平台的GUI应用程序开发框架，基于NodeJS/OpenGL

目标：在此基础上开发GUI应用程序可拥有开发WEB应用般简单与速度同时兼顾Native应用程序的性能与体验


* Only `iOS` and `Android` systems are supported for the time being, this does not include `AndroidTV`, because `TV` applications are very different from mobile applications

* From here, [`Go API Index`](http://shark.io/doc/) can go to `API Documents Index`

| ![Screenshot](http://shark.io/img/0x0ss.jpg) | ![Screenshot](http://shark.io/img/0x0ss_3.jpg) | ![Screenshot](http://shark.io/img/0x0ss_4.jpg) |
|--|--|--|


Build and install shark-tools
===============

1. Build must dependent `Xcode` / `JDK1.7` / `Android-SDK-23` / `NDK` / `python` / `nodejs` / `yasm`.

2. Setting environment variable `JAVA_HOME` and `ANDROID_HOME`

Compile and install shark tools `make install`, It takes a long time.

use shark tools create project.

first create an empty file directory, then execute in the directory

`shark init`

export ios xcode project `shark export ios`


# Simple Examples

This is a simple program to display Hello world on the screen

```jsx
import { GUIApplication, Root } from 'shark'
new GUIApplication().start(
	<Root>hello world!</Root>
)
```

You can get a more detailed [`Examples`]

# Start Usage

If you've never used Shark before, you can start from here and build your Shark program step by step.

## Install shark-tools

First, you need to install the toolkit provided by `Shark`

* Install `shark-tools` using nodejs `npm` 

* Open `Terminal` and execute the following command：

```sh
# shell
$ sudo npm install -g shark-tools

```
	
* Running `shark-tools` requires dependency on `nodejs` and `python2.7`

* And now do not support the `windows` system, you need to use it under `mac`

## Create new project

Create a new `Shark` project using the following `shell` command：

```sh
# shell
$ mkdir myproject
$ cd myproject
$ shark init
```

## Build project

This step compresses and packages the JavaScript code and resource files inside the project,
If this is a new project, you can skip this step and go directly to the next step

```js
# shell
$ shark build
```

## Export project

This step exports [`Xcode`] or [`Android Studio`] project，because you eventually publish the program that be a `.apk` or `.ipa`

```js
# shell
# export xcode ios project
$ shark export ios
# export android studio project
$ shark export android
```

After exporting the project, next you can open it using [`Xcode`] and [`Android Studio`]

## Shark test http server

`shark-tools` provides a test http server, each time you change the `js` or `jsx` code, you don't have to reinstall every time.

Execute the following code to start it：

```js
# shell
$ shark
```

# Downloads

* Examples demo [`Android APK`] Install package

* Project [`Source code`] from `Github`


[`Examples`]: https://github.com/louis-tru/shark/tree/master/demo
[`Xcode`]: https://developer.apple.com/library/content/documentation/IDEs/Conceptual/AppDistributionGuide/ConfiguringYourApp/ConfiguringYourApp.html
[`Android Studio`]: https://developer.android.com/studio/projects/create-project.html
[`Android APK`]: https://github.com/louis-tru/shark/releases/download/v0.1.0/examples-release.apk
[`NPM`]: https://www.npmjs.com/package/shark-tools
[`Source code`]: https://github.com/louis-tru/shark
