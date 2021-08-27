How long it takes your webpage to load isn’t the only issue. Based on a Google article, if your webpage has poor performance, 
79% of your visitors say they’re less likely to purchase from your website again (https://www.thinkwithgoogle.com/marketing-resources/experience-design/mobile-page-speed-load-time/).


As web technologies have advanced, there’s been a push to move more and more applications to the web. This has presented developers with another challenge because web browsers support only one programming language: JavaScript.

Having only one programming language across all browsers is a good thing in one sense because you only have to write your code once and you know that it will run in each browser. You still have to test in each browser that you intend to support because browser vendors sometimes implement things slightly different compared to other browsers. Also, sometimes one browser vendor won’t add a new feature at the same time as other vendors. Overall though, having one language to support is easier than four or five. The downside of browsers supporting only JavaScript, however, is that the applications we want to move to the web weren’t written in JavaScript but rather with languages like C++.

JavaScript is a great programming language but we’re now asking it to do more than it was originally designed to do, like heavy computations for games for example, and we’re asking for it to run really fast.



  What is WebAssembly?

WebAssembly is a low-level assembly-like language that can run at near native speeds in all modern desktop web browsers as well as many mobile web browsers.
    
    WebAssembly is designed as a compile target so that code written in languages like C++, Rust, and others can now run on the web.

    Back-end developers can leverage WebAssembly to improve code reuse or to bring their code to the web without having to rewrite it. Web developers also benefit with the creation of new libraries, improvements to existing libraries, and the opportunity to improve performance in computationally heavy sections of their own code.
    Although the primary use of WebAssembly at the moment is within web browsers, WebAssembly is also being designed with portability in mind, so that it can be used outside of the browser as well.

What problems does it solve?

One of the biggest issues that WebAssembly aims to solve is performance—from how long it takes to download your code to how quickly the code executes.

What problems does it solve?

With programming languages, rather than writing code in the machine language that the computer’s processor understands, 1s and 0s (also referred to as native code), you usually write something that’s closer to a human language. While it’s easier to work with code that’s abstracted from the fine details of a computer, computer processors don’t understand your code so, when it comes time to run it, you have to convert what you wrote into machine code.


Performance improvements

The advantage of languages that are interpreted is that there’s no need to compile the code ahead of time which means the code starts running sooner. The downside, however, is that the interpreter has to convert the instructions to machine code every time the code is run. If your code is doing a loop for example, each line of that loop has to be interpreted every time the loop is executed. Because there’s not always a lot of time available during the interpretation process, optimizations are not always possible either.

Other programming languages, like C++, are not interpreted. With these types of languages, you need to convert the instructions to machine code ahead of time and, to do this, there are special programs called compilers that handle the task.

With compiled programming languages, it takes a bit of time up front to convert the instructions to machine code before you can run them but the advantage is that there’s more time available to run optimizations on the code and, once it’s compiled to machine code, it doesn’t have to be compiled again.

Over time, JavaScript has gone from simply being a glue language that ties components together, and where it was only expected to be short lived, to a language that is now used by many websites to do complex processing, can easily involve hundreds to thousands of lines of code and, with the rise of single page applications, the code can often be long lived. The internet has gone from having websites that just displayed some text and a few pictures to very interactive websites and even websites that are called web applications because they’re similar to desktop applications but running in a web browser.

As developers continued to push the limits of JavaScript, some noticeable performance issues came to light. Browser makers decided to try and find a middle ground where you still get the advantages of an interpreter, where the code starts running as soon as it gets called, but also have code that runs faster when it’s being executed. To make the code faster, they introduced a concept called JIT (Just in Time compiling) where the JavaScript engine monitors the code as it runs and, if a section of code is used enough times, the engine will attempt to compile that section of code into machine code so that it can bypass the JavaScript engine and use the lower-level system methods instead which are much faster.

The reason why the JavaScript engine needs to monitor the code a number of times before it gets compiled to machine code is because JavaScript is also a dynamic programming language. In JavaScript a variable can hold any type of value. For example, a variable can hold an integer initially but later the variable can be assigned a string. Until the code is run a few times, a browser doesn’t know what to expect. Even when compiled, the code still needs to be monitored because there’s still a chance that something will change and the compiled code for that section would need to be thrown out and the process started again.


As browser makers continued to look for ways to improve the performance of JavaScript, Mozilla (the maker of the Firefox browser) defined a subset of JavaScript that they called asm.js.


##  asm.js, the forerunner to WebAssembly

You don’t write asm.js directly. Instead, you write your logic using C or C++ and convert it into JavaScript. Converting code from one language to another is known as transpiling.

Asm.js brought the following advantages:

    The following code snippet shows an example of asm.js code:
    Faster code execution for high computations. When the JavaScript engine of the browser sees a special string called the asm pragma statement ("use asm";), it acts as a flag telling the browser that it can use the low-level system operations rather than the more expensive JavaScript operations.
    Despite the advantages that asm.js brought, there are still some shortcomings:

As the browser makers looked at how they could improve upon asm.js, they came up with a WebAssembly MVP where the goal was to take the positive aspects of asm.js and, at the same time, address its shortcomings.


1.2.3   Faster startup times compared with JavaScript
1.2.4   Ability to use languages other than JavaScript in the browser

Up until this point, for a language other than JavaScript to be able to target the web, the code had to be converted to JavaScript. JavaScript is a programming language and was not intended to be a compiler target.

WebAssembly, on the other hand, is designed to be a compiler target from the beginning which means developers who want to use a particular language for web development will be able to do so without having to transpile their code into JavaScript.

Because WebAssembly isn’t tied to the JavaScript language, improvements can be made to the technology more easily and without worrying about interfering with how JavaScript works. This independence should result in the ability to make improvements to WebAssembly much faster.

For the MVP of WebAssembly, focus was given to C and C++ as the languages that could target WebAssembly but Rust has since added support and several other languages are experimenting with WebAssembly.



1.2.4   Ability to use languages other than JavaScript in the browser

Being able to take code written in languages other than JavaScript and compile them to WebAssembly gives developers more flexibility when it comes to code reuse. Now, something that would have had to be rewritten in JavaScript can still be used on the desktop or server but can also run in the browser.
1.3   How does it work?

As the following diagram illustrates (figure 1.1), with JavaScript, the code is included in the website and is interpreted as it runs. Because JavaScript variables are dynamic, looking at the add method in the illustration, it’s not obvious what type of values you’re dealing with. The variables a and b could be integers, floats, strings, or even a combination where one variable could be a string and the other a float for example.

The only way to know for sure what the types are is by monitoring the code as it executes which is what the JavaScript engine does. Once the JavaScript engine is satisfied that it knows the variable’s types then it can convert that section of code into machine code.
1.2.5   Opportunity for code reuse

WebAssembly is not interpreted but rather it’s compiled into the WebAssembly binary format by a developer ahead of time, as the following high-level illustration shows (figure 1.2). Because the variable types are all known ahead of time, when the browser loads the WebAssembly file, the JavaScript engine doesn’t need to monitor the code. It can simply compile the binary format of the code straight into machine code.
1.3   How does it work?
1.3.1   Overview of how compilers work

In section 1.2.1, we talked briefly about how developers write code in a language that’s closer to a human language but computer processors only understand machine language. As a result, the code you write has to be converted into machine code in order for it to be executed. What we didn’t mention is that each type of computer processor has its own type of machine code.



1.3.1   Overview of how compilers work

The bytecode in your Wasm file isn’t machine code yet. It’s simply a set of virtual instructions that browsers, who support WebAssembly, understand. As shown in figure 1.5, when the file is loaded into a browser that supports WebAssembly, the browser verifies that everything is valid and then the bytecode is compiled the rest of the way into the machine code of the device that the browser is running on.

At the time of writing, the process of downloading the Wasm file into the browser and having the browser compile it is done by making some JavaScript method calls. There’s a desire to allow WebAssembly modules to interact with ES6 modules in the future, including the ability to be loaded though a special HTML tag (<script type="module">) but this isn’t yet available for WebAssembly modules.


Once a browser has compiled the WebAssembly bytecode into machine code, the compiled module can be passed to a Web Worker (we’ll dig into Web Workers in chapter 9 but, for now, Web Workers are a way to create threads in JavaScript) or to another browser window. The compiled module can even be used to create additional instances of the module.




1.3.2   Loading, compiling, and instantiating a module

Up until now, the only language allowed to run within the JavaScript virtual machine (VM) was JavaScript. When other technologies were tried over the years, like plug-ins, they needed to create their own sandboxed VM, which increased the attack surface and increased the use of computer resources. For the first time ever, the JavaScript VM is being opened up to allow WebAssembly code to also run in the same VM. WebAssembly code being able to be run in the same VM as JavaScript has several advantages. One of the biggest advantages to reusing the JavaScript VM for WebAssembly is that the VM has been heavily tested and hardened against security vulnerabilities over the years. If a new VM was created, it would undoubtedly have some security issues to iron out.

WebAssembly is being designed as a complement to JavaScript and not as a replacement. Although we’ll likely see some developers try to create entire websites using only WebAssembly, that likely will not be the norm. There will be times where JavaScript will still be the better choice. There will also be times when a website may need to include WebAssembly for access to faster calculations or for lower level support. For example, SIMD (Single Instruction, Multiple Data)—the ability to process multiple data with a single instruction)—was being built into the JavaScript of several browsers but the browser vendors decided to deprecate the JavaScript implementation and make SIMD support available only via WebAssembly modules. As a result, if your website needs SIMD support, you would need to include a WebAssembly module to communicate with.

When programming for a web browser, there are basically two main components. The JavaScript VM, which the WebAssembly module runs in, and the Web APIs (for example, DOM, WebGL, Web Workers, and so on). Being an MVP, there are some things missing from WebAssembly. Your WebAssembly module can communicate with JavaScript but doesn’t yet have the ability to talk directly to any of the Web APIs. There is a post-MVP feature being worked on called Host Bindings which will give WebAssembly direct access to the Web APIs. In the meantime, however, modules can interact with the Web APIs indirectly by calling into JavaScript and having JavaScript perform the action needed on the module’s behalf.



Boolean values are represented using a 32-bit integer where 0 is false and a non-zero value is true. All other value types, like strings for example, need to be represented in the module’s linear memory.
1.4   Structure of a WebAssembly module

WebAssembly currently has only four available value types:

    The following is a brief overview of a WebAssembly module’s structure. You’ll learn about a module’s structure in more detail in chapter 2.
    1.4.1   Preamble

    A Wasm file starts out with what’s called the preamble which contains a magic number (0x00 0x61 0x73 0x6D which is ‘\0asm’) that distinguishes a WebAssembly module from an ES6 module (ES is shorthand for ECMAScript and 6 is the version. ECMAScript is the official name for JavaScript).

    The magic number is then followed by a version (0x01 0x00 0x00 0x00 which is 1). One of the goals with WebAssembly is to keep everything backwards compatible as new features are being added and to not have to increase the version number. If there ever happens to be something that cannot be implemented without breaking things then the version number will be increased.

Following the preamble, a module can have several sections but each section is optional so you could technically have an empty module with no sections. You’ll learn about one use case for an empty module in chapter 3 when you implement feature detection to check if WebAssembly is supported in a web browser.

There are two types of sections available: Known sections and Custom sections.


1.4.2   Known sections

Known sections can be included only once and must appear in a specific order.
1.4.1   Preamble
1.4.3   Custom sections

A Custom section provides a way to include data inside the module for uses that don’t apply to the Known sections. Custom sections can appear anywhere in the module (before, in between, or after the Known sections), any number of times, and multiple custom sections can even reuse the same name.

Unlike with the Known sections, if a Custom section isn’t laid out correctly it won’t trigger a validation error. Custom sections can be loaded lazily by the framework which means the data they contain might not be available until some point after the initialization of the module.

For the MVP of WebAssembly, a Custom section called “name” was defined. The idea with this section is that you could have a debug version of your WebAssembly module and this section would hold the names of the functions and variables in text form to use when debugging. Unlike with other Custom sections, this section should only appear once and only after the Data section.
1.4.2   Known sections

WebAssembly has been designed with the openness of the web in mind. Just because the binary format isn’t designed to be written or read by humans doesn’t mean that WebAssembly modules are a way for developers to try and hide their code. Actually, quite the opposite is true. A text format that uses s-expressions has been defined for WebAssembly that corresponds to the binary format.
Info
1.4.3   Custom sections

The text format will allow for the View Source of the code in a browser, for example, or it can be used for debugging purposes. It’s even possible to write s-expressions by hand and, by using a special compiler, compile the code into the WebAssembly binary format.

Because the WebAssembly Text Format will be used by browsers when you choose to View Source and for debugging purposes, having a basic understanding of the text format will be useful. For example, since all sections of a module are optional, you could define an empty module using the following s-expression: (module)

If you were to compile the (module) s-expression, into the WebAssembly binary format and look at the resulting binary values, the file would only contain the preamble bytes (0061 736d – the magic number, and 0100 0000 – the version number).
1.5   WebAssembly Text Format

In chapter 11, you’ll create several WebAssembly modules using only the text format, so that you’ll have a better idea of what you’re looking at if you ever need to debug a module in a browser for example.
Info

One of the ways that WebAssembly is secure is due to it being the first language to ever share the JavaScript VM. The JavaScript VM is sandboxed from the runtime and has had years of hardening and security tests to make it secure. WebAssembly modules don’t have access to anything that JavaScript doesn’t have access to and will also respect the same security policies as JavaScript which includes enforcing things like same-origin policy.

Unlike a desktop application, a WebAssembly module doesn’t have direct access to the memory of the device. Instead, the runtime environment passes the module an ArrayBuffer during initialization. The module uses the ArrayBuffer as linear memory and the WebAssembly framework checks to make sure that the code is operating within the bounds of the array.

A WebAssembly module doesn’t have direct access to items, like function pointers, that are stored in the Table section. The code asks the WebAssembly framework to access an item based on its index. The framework then accesses the memory and executes the item on the code’s behalf.

In C++, the execution stack is in memory along with the linear memory and, although the C++ code isn’t supposed to modify the execution stack, it’s possible to do so through the use of pointers. WebAssembly’s execution stack is also separate from the linear memory and is not accessible by the code.



1.6   How is WebAssembly secure?

To create the MVP, the initial focus of WebAssembly was on the C and C++ languages but Rust has since added support for WebAssembly. It’s also possible to write code using the WebAssembly Text format, which uses s-expressions, and compile that into WebAssembly using a special compiler.

Right now, the MVP of WebAssembly does not have garbage collection (GC) which limits what some languages can do. Garbage collection is being worked on as a post-MVP feature but, until it arrives, several languages are experimenting with WebAssembly by either compiling their VM to WebAssembly or, in some cases, by including their own garbage collector.

The following are several languages that are experimenting with WebAssembly support:
AssemblyScript is a new compiler that takes TypeScript and turns it into WebAssembly. Converting TypeScript makes sense considering TypeScript is typed and currently transpiles to JavaScript already.
More information

For the purpose of learning WebAssembly in this book, we’ll use the C and C++ languages.



1.7   What languages can I use to create a WebAssembly module?

In 2017 all of the modern browser makers released versions of their browsers that support the MVP of WebAssembly. The desktop browsers that support WebAssembly are Chrome, Edge, Firefox, Opera, and Safari.

Several of the mobile web browsers that also support WebAssembly are Chrome, Firefox for Android, and Safari.

As mentioned at the beginning of this chapter, WebAssembly was designed with portability in mind so that it can be used in multiple locations, not just in a browser. One of the non-browser locations that WebAssembly modules are also supported in is NodeJS starting with version 8.

    NodeJS is a JavaScript runtime built using Chrome’s V8 JavaScript engine that allows JavaScript code to be used server-side. Similar to how many developers see WebAssembly as an opportunity to use code that they are familiar with in the browser, rather than JavaScript, NodeJS gives the opportunity for developers who prefer JavaScript to also use it on the server-side.

    WebAssembly isn’t a replacement to JavaScript but rather a compliment to it. There are times where using a WebAssembly module will be a better choice and other times where using JavaScript will be the better choice. Running in the same virtual machine as JavaScript allows both technologies to leverage each other.

    WebAssembly will open the door for developers, who are proficient in languages other than JavaScript, to be able to make their code available on the web. It will also allow web developers, who may or may not know how to code in languages like C or C++, to gain access to newer and faster libraries and potentially with features not available in the current JavaScript libraries. In some cases, WebAssembly modules might be used by libraries to speed up execution of certain aspects of the library and, other than faster code, the library would work the same as it always has.

    The most exciting thing about WebAssembly is that it’s already available in all major desktop browsers, in several major mobile browsers, and even outside of the browser in NodeJS.
    1.9   Summary

As you saw in this chapter, WebAssembly brings a number of improvements with many being around performance as well as language choice and code reuse. Some of the key improvements that WebAssembly brings are the following:
1.8   Where can I use my module?
The ability to use code written in a language, other than JavaScript, in a browser.

Increased opportunity for code reuse by structuring the WebAssembly framework in such a way that it can be used in the browser and outside of the browser.
